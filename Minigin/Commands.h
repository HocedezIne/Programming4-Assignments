#pragma once
#include "GameObject.h"

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
}