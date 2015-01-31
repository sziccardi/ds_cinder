#pragma once

#ifndef DS_UI_TOUCH_FIVE_FINGER_CLUSTER
#define DS_UI_TOUCH_FIVE_FINGER_CLUSTER

#include <functional>
#include <vector>

#include <Poco/Timestamp.h>

#include <cinder/Rect.h>

#include <ds/ui/touch/touch_info.h>

namespace ds{
namespace ui{

/*
 * FiveFingerCluster is a class that grabs touch info from wherever (you can pipe it directly from the Engine if you want)
 * and parses it into clusters. If you want all the cluster info, listen to cluster update callback. If you just want to know if a cluster has been 
 * held in the same spot long enough to trigger, listen to TriggeredCallback (only calls when it's triggered) or triggerable (which lets you know if the cluster later gets invalidated)
 * 
 * Any number of clusters (of any finger number) are allowed. Each can be triggered / triggerable.
 */

class FiveFingerCluster {
public:

	class Cluster {
	public:
		Cluster(): mTriggerable(false), mMaxTouches(0){};
		int								mClusterId;
		ci::Rectf						mBoundingBox;
		ci::Rectf						mCurrentBoundingBox;
		std::vector<ds::ui::TouchInfo>	mTouches;
		int								mMaxTouches;
		bool							mTriggerable;
		Poco::Timestamp::TimeVal		mInitialTouchTime;

		void							addToBoundingBox(ci::Vec3f point, ci::Rectf& boxToEdit);
		void							configureCurrentBoundingBox();
	};

	FiveFingerCluster(float secondsToTrigger = 2.0f, int minTouches = 5, float boundingBoxSize = 200.0f);
	~FiveFingerCluster();

	// How far a touch can be away from any other touch to be counted as part of it's cluster.
	void							setMinClusterSeparation(const float minSeparation){ mMinClusterSeparation = minSeparation; }

	void							parseTouch(const ds::ui::TouchInfo& ti);

	// gets called when all fingers are released and it's triggerable
	void							setTriggeredCallback( const std::function<void (const ci::Vec2f cent)> &func );

	// gets called when the triggerable state changes. For example, when you've held it down long enough, it calls this with a "true" param.
	void							setTriggerableCallback( const std::function<void (const bool triggerable, const ci::Vec2f cent)> &func );

	void							setClusterUpdateCallback( const std::function<void (const ds::ui::TouchInfo::Phase clusterPhase, const Cluster&)> &func);

private:


	// these three variables are what determine what is triggerable.
	float							mTriggerTime;
	int								mMinTouches;
	float							mBoundingBoxSize;
	float							mMinClusterSeparation;

	int								mMaxClusterId;


	std::vector<Cluster>			mClusters;

	// answers with the cluster index if it's close to a cluster.
	// if the point is not close enough, it responds with -1
	int								closeToCluster(ci::Vec3f pos);

	int								findCluster(int fingerId, ci::Vec3f curPos);

	std::function<void (const ci::Vec2f)>				mTriggeredFunction;
	std::function<void (const bool, const ci::Vec2f)>	mTriggerableFunction;
	std::function<void (const ds::ui::TouchInfo::Phase, const Cluster&)>	mClusterUpdateFunction;
};

} // namespace ui
} // namespace ds
#endif