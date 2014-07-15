#include "CMImage.h"

CCSprite* CMImage::create(void *data, CCNode *parent, int nZOrder, bool bVisible)
{
	if ((NULL == data) || (NULL == parent))
	{
		return NULL;
	}

	ImageData *p = (ImageData *)data;
	CCSprite *pSprite = CCSprite::create(p->m_strPath.c_str());
	if (NULL != pSprite)
	{
		pSprite->setPosition(p->m_Position);
		pSprite->setVisible(bVisible);
		parent->addChild(pSprite, nZOrder);
	}

	return pSprite;
}

CCSprite* CMImage::create(void *data, CCNode *parent, int nZOrder, int nTag, bool bVisible)
{
	CCSprite* pSprite = create(data, parent, nZOrder, bVisible);
	if (NULL != pSprite)
	{
		pSprite->setTag(nTag);
	}

	return pSprite;
}

CCSprite* CMImage::create(void *data, CCNode *parent, int nZOrder, int nTag, const CCPoint& anchor, bool bVisible)
{
	CCSprite* pSprite = create(data, parent, nZOrder, nTag, bVisible);
	if (NULL != pSprite)
	{
		pSprite->setAnchorPoint(anchor);
	}

	return pSprite;
}