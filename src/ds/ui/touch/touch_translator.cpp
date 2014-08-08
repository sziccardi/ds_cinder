#include "touch_translator.h"

namespace ds {
namespace ui {

/**
 * \class ds::ui::TouchTranslator
 */
TouchTranslator::TouchTranslator()
		: mTx(0.0f)
		, mTy(0.0f)
		, mSx(1.0f)
		, mSy(1.0f) {
}

ci::Vec2i TouchTranslator::toWorldi(const int x, const int y) const {
	const ci::Vec2f		f(toWorldf(static_cast<float>(x), static_cast<float>(y)));
	return ci::Vec2i(	static_cast<int>(f.x),
						static_cast<int>(f.y));
}

ci::Vec2f TouchTranslator::toWorldf(const float x, const float y) const {
	return ci::Vec2f(	mTx + (x * mSx),
						mTy + (y * mSy));
}

void TouchTranslator::setTranslation(const float x, const float y) {
	mTx = x;
	mTy = y;
}

void TouchTranslator::setScale(const float x, const float y) {
	mSx = x;
	mSy = y;
}

} // namespace ui
} // namespace ds