#pragma once
#ifndef _TEXT_LEAK_TESTER_APP_MODEL_ALLDATA_H_
#define _TEXT_LEAK_TESTER_APP_MODEL_ALLDATA_H_

#include "model/generated/story_model.h"

namespace downstream {

/**
 * \class downstream::AllData
 */
class AllData {
public:
	
	AllData(){};

	std::vector<ds::model::StoryRef>	mStories;

};

} // !namespace downstream

#endif // !_TEXT_LEAK_TESTER_APP_MODEL_ALLDATA_H_

