#include "GestureRecEngine.h"



GestureRecEngine::GestureRecEngine()
{
}


GestureRecEngine::~GestureRecEngine()
{
}

void GestureRecEngine::addGesture(GestureInterface *gest)
{
	gestures.push_back(gest);
}

GestureInterface * GestureRecEngine::checkForGesture(nite::Skeleton s)
{

	for (auto g: gestures)
	{
		g->updateSkeleton(s);
		if (g->checkForGesture())
		{
			return g;
		}
	}
	return nullptr;
}

std::vector<GestureInterface*> GestureRecEngine::checkForDoingGestures(nite::Skeleton s)
{
	std::vector<GestureInterface*> temp;

	for (auto g : gestures)
	{
		g->updateSkeleton(s);
		if (g->checkForDoingGesture())
		{
			temp.push_back(g);
		}
	}
	return temp;
}
