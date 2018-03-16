# Content Model

## The "M" in "MVC"

The "VC" stands for very cool. New, as of March 2018.

ContentModel greatly simplifies defining a data model and pulling it out of a sqlite database. There's a simple XML descriptor that describes which tables your interested in, links Resources, builds hierarchies, and allows control of the SQL queries. ContentModel is string-based, so any type of data can be stored in it, and it can be applied to layout files at runtime.

Let's say you have a table in a sqlite db called "slides". (Check out the getting_started example db for a real-life example.)

    CREATE TABLE "slides" ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, `title` TEXT, `body` TEXT, `resourceid` TEXT, `sort_order` INTEGER, `layout` TEXT, `local_resource` TEXT, `markdown_file` TEXT )
	
To tell ContentQuery to grab that table, you'd add an entry in data/model/content_model.xml:

   	<table name="slides"/>
	
ContentQuery would automatically get all the rows and columns from that table and make children and properties from them, respectively. Here's what the data structure would look like if we were to call mEngine.mContent.printTree(true, "") in the app:

````
ContentModel id:0 name:root label:The root of all content
              prop:current_slide value:6
      ContentModel id:0 name:sqlite label:The root of all sqlite data
                prop:model_xml value:%APP%/data/model/content_model.xml
        ContentModel id:1 name:slides label:SQLite Table
                  prop:depth value:1
                  prop:label_field value:title
                  prop:name value:slides
                  prop:parent_id value:0
                  prop:resources value:resourceid
                  prop:sort value:sort_order ASC
          ContentModel id:1 name:slides label:Downstream::Cinder
                    prop:body value:An app framework in C++, based on cinder.
                    prop:id value:1
                    prop:layout value:intro.xml
                    prop:local_resource value:%APP%/data/images/slides/lisa_frank_calendar.png
                    prop:markdown_file value:
                    prop:resourceid value:0
                    prop:sort_order value:0
                    prop:title value:Downstream::Cinder
          ContentModel id:2 name:slides label:Environment Setup
                    prop:body value:Getting a system setup to compile ds_cinder
                    prop:id value:2
                    prop:layout value:scroller.xml
                    prop:local_resource value:%APP%/data/images/slides/whynot.png
                    prop:markdown_file value:%DS_PLATFORM_090%/README.md
                    prop:resourceid value:0
                    prop:sort_order value:10
                    prop:title value:Environment Setup
````

There's a few things to note here:

* There's an automatic child created on the root object named "sqlite"
* The "sqlite" table is where all ContentWrangler content goes by default
* This setup is so you - or the system in the future - can be expanded to add more children to the root if needed
* Each sqlite table is created as it's own model as a child of the "sqlite" node.
* Each row from the sqlite database is created as a child of the table.
* Each child gets a series of properties based on the columns of that table

To simplify the above:

````
- root
	- sqlite
		- slides
			- slides row
			- slides row
			- slides row
			etc.
````

Now that the content is in the app, we'll want to access it. To get the slides table:

    auto slidesTableModel = mEngine.mContent.getChildByName("sqlite.slides");
	
* mEngine.mContent IS the root, so we're starting from there. 
* getChildByName() uses dot notation to look further down the tree. That assumes the first child with that name is the one you want
* If there's no model with a given name, it will return an empty data model, which you can check for using mContentModel.empty()

So we've got a reference to our slides table, and we want to do something with each slide:

````
	if(slidesTableModel.empty()){
		DS_LOG_WARNING("Slides table is empty!");
	}

	for(auto it : slidesTableModel.getChildren()){
		buildSlide(it);
	}
````

It's important to do sanity checks on the models, so if something doesn't show up in your app you know where to start looking.

## Specifying content models

The content_model.xml file can specify a bunch of things about your data model. 

### Query control

**select**: Overrides the default select statement with your own. The default is "SELECT * FROM ". Example: "SELECT id, name FROM "
**where**: Add your own WHERE clause. The default is empty. Example: "approved=1"
**sort**: Add your own ORDER BY clause. The default is empty. You can comma separate these. Example: "name ASC, date_added DESC"
**limit**: Limit the number of entries. Example: "10"

The app logic is like this:

    select + where + sort + limit.

The input of:

````XML
	<table name="posts"
		select="SELECT p.imageid AS priamryimage FROM posts p INNER JOIN tile t ON p.tileid = t.id"
		where="p.approvalstatus=1"
		sort="p.created_at ASC"
		limit="10"
		/>
````

Produces a SQL statement of:

    SELECT p.imageid AS priamryimage INNER JOIN tile t ON p.tileid = t.id WHERE p.approvalstatus=1 ORDER BY p.created_at ASC LIMIT 10

If you want to specify the entire statement yourself, just use the select parameter and skip everything else.

### Field hinting

**resources**: A comma-space separate list of columns that map to the resources table. Example: "primary_image, thumbnail_image". These automatically get mapped to ds::Resource values
**id**: The query automatically picks the primary key column to be the id, but if you want to override that you can specify an id field here. Example: "title_id"
**name_field": The name for each item is inherited from it's parent, but if you want to override that specify a field here. Example: "title"
**label_field": Labels are just a helpful field for humans. Specify a field to display here. Example: "subtitle"

````XML
	<table name="slides"
		id="special_id"
		name_field="title"
		label_field="subtitle"
		resources="primary_image, thumbnail_image"
		/>
````

### Parent-child relationships

Nest xml tables to indicate a relationship and specify what the foreign key is.

**child_local_id**: The column in THIS table that matches the parent's primary key. This is for parents with multiple children. Example: "slide_id"

In the below example, there are multiple slide_items for each slide. The slide_items table has a column "slide_id" that matches the primary key of the "slides" table. 

````XML
	<table name="slides"
		sort="sort_order ASC"
		resources="resourceid"
		label="title"
		>
		<table name="slide_items"
			child_local_id="slide_id"
			label="name"
			/>
	</table>
````


**parent_foreign_id**: The column in the PARENT table that matches this primary key. This is for parents with a single child. Example: "slide_theme_id"

There is one theme per slide, and the "slides" table has a "slide_theme_id" column.

````XML
	<table name="slides"
		sort="sort_order ASC"
		resources="resourceid"
		label="title"
		>
		<table name="slide_theme"
			parent_foreign_id="slide_theme_id"
			label="name"
			/>
		<table name="slide_items"
			child_local_id="slide_id"
			label="name"
			/>
	</table>
````

When these get queried, you'll get a data structure like this:

````XML
- root
	- sqlite
		- slides
			- slides row
				- slide_theme row
				- slide_items row
				- slide_items row
			- slides row
				- slide_theme row
				- slide_items row
				etc.
````