#pragma once
#include "GameObject.h"
#include "Observer.h"

namespace engine
{
	class Command
	{
	public:
		Command() = default;
		Command(const Command& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(Command&& other) = delete;

		virtual ~Command() = default;

		virtual void Execute(const float deltaTime) = 0;
	};

	class GameObjectCommand : public Command
	{
	public:
		GameObjectCommand(GameObject* go) : Command(), m_GO(go) {};

		GameObjectCommand(const GameObjectCommand& other) = delete;
		GameObjectCommand& operator=(const GameObjectCommand& other) = delete;
		GameObjectCommand(GameObjectCommand&& other) = delete;
		GameObjectCommand& operator=(GameObjectCommand&& other) = delete;

		virtual ~GameObjectCommand() = default;

	protected:
		GameObject* GetGameObject() const { return m_GO; };

	private:
		GameObject* m_GO;
	};

	class MoveCommand final : public GameObjectCommand
	{
	public:
		MoveCommand(GameObject* go, const glm::vec3 direction,  const float speed) : GameObjectCommand(go),
		m_Direction(direction), m_Speed(speed) {};

		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;

		virtual ~MoveCommand() = default;

		virtual void Execute(const float deltaTime) override
		{ 
			GetGameObject()->SetLocalPosition(GetGameObject()->GetLocalPosition() + (m_Direction * m_Speed * deltaTime)); 
		};

	private:
		const glm::vec3 m_Direction;
		const float m_Speed;
	};

	class KillCommand final : public Command, public Subject
	{
	public:
		KillCommand() : Command() {};

		KillCommand(const KillCommand& other) = delete;
		KillCommand& operator=(const KillCommand& other) = delete;
		KillCommand(KillCommand&& other) = delete;
		KillCommand& operator=(KillCommand&& other) = delete;

		virtual ~KillCommand() = default;

		virtual void Execute(const float deltaTime) override
		{
			deltaTime;

			NotifyObservers(this, Event::PlayerDied, std::tuple<>());
		};
	};

	class ScoreCommand final : public Command, public Subject
	{
	public:
		ScoreCommand(int value) : Command(), m_ScoreValue(value) {};

		ScoreCommand(const ScoreCommand& other) = delete;
		ScoreCommand& operator=(const ScoreCommand& other) = delete;
		ScoreCommand(ScoreCommand&& other) = delete;
		ScoreCommand& operator=(ScoreCommand&& other) = delete;

		virtual ~ScoreCommand() = default;

		virtual void Execute(const float deltaTime) override
		{
			deltaTime;

			NotifyObservers(this, Event::EnemyDied, m_ScoreValue);
		};

	private:
		const int m_ScoreValue;
	};
}