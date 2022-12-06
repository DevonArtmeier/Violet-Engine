/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Actor pool
	/// </summary>
	std::unique_ptr<std::vector<std::shared_ptr<Actor>>> Actor::pool;

	/// <summary>
	/// Initialize actor pool
	/// </summary>
	void Actor::InitPool() {
		pool = std::make_unique<std::vector<std::shared_ptr<Actor>>>();
	}

	/// <summary>
	/// Dispose of actor pool
	/// </summary>
	void Actor::DisposePool() {
		DisposeAll();
		pool = nullptr;
	}

	/// <summary>
	/// Add actor to pool
	/// </summary>
	/// <param name="actor">Actor to add</param>
	void Actor::Add(std::shared_ptr<Actor> actor) {
		if (actor) {
			Engine::DebugMessage("ACTOR SPAWN:         " + actor->ToString());
			pool->push_back(actor);

			LayerType layerType = Graphics::curLayerType;
			Graphics::curLayerType = LayerType::Actor;
			actor->OnSpawn();
			Graphics::curLayerType = layerType;
		}
	}

	/// <summary>
	/// Update actors
	/// </summary>
	/// <param name="mode">Update mode</param>
	void Actor::Update(UpdateMode mode) {
		for (int i = 0; i < pool->size(); ++i) {
			std::shared_ptr<Actor> actor = pool->at(i);

			switch (mode) {
			case UpdateMode::Normal:
				actor->OnUpdate();
				break;
			case UpdateMode::Fixed:
				actor->OnFixedUpdate();
				break;
			case UpdateMode::Draw:
				actor->OnDraw();
				break;
			}

			if (actor->disposed) {
				Engine::DebugMessage("ACTOR DISPOSE:       " + pool->at(i)->ToString());
				actor->OnDispose();
				pool->erase(pool->begin() + i--);
			}
		}
	}

	/// <summary>
	/// Dispose of all actors
	/// </summary>
	void Actor::DisposeAll() {
		for (int i = 0; i < pool->size(); ++i) {
			Engine::DebugMessage("ACTOR DISPOSE:       " + pool->at(i)->ToString());
			pool->at(i)->OnDispose();
		}
		pool->clear();
	}

	/// <summary>
	/// Dispose of actor
	/// </summary>
	void Actor::Dispose() {
		disposed = true;
	}

}
