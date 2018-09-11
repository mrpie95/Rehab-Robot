#include "GestureRecEngine.h"



GestureRecEngine::GestureRecEngine()
{
}


GestureRecEngine::~GestureRecEngine()
{
}

void GestureRecEngine::addGesture(Gesture *gest)
{
	gestures.push_back(gest);
}

Gesture * GestureRecEngine::checkForGesture(nite::Skeleton s)
{
	Gesture* temp = nullptr;
	for (auto g: gestures)
	{
		g->updateSkeleton(s);
		if (g->checkForGesture())
		{
			temp = g;
		}
	}
	return temp;
}

std::vector<Gesture*> GestureRecEngine::checkForDoingGestures(nite::Skeleton s)
{
	std::vector<Gesture*> temp;

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
