# Tool System
A modular tool interaction and minigame gameplay system built with **Unreal Engine 5 (C++)**.

**This system is under active development and is being expanded with additional tools and minigames.**

---

## Overview

The Tool System is a gameplay system designed to support tool-based interactions and minigame-driven gameplay mechanics.

The Tool System is composed of two main layers:

### 1. **Tools**
Tools are the primary interaction drivers within the system.
Each tool is implemented as a C++-based, modular gameplay object responsible for initiating and managing interactions with compatible devices.

From a technical perspective, tools are derived from a common ToolBase class. This design allows for easy extension and addition of new tools. New tools can be created by inheriting from the ToolBase class and implementing specific interaction logic.

#### Example tools include:
- Electrical Fix Device
- Terminal Hack Device

### 2. **Minigames**
Minigames are interactive sequences that players can engage with using the tools. Each minigame is designed to provide a unique challenge or task that players must complete using the associated tool. Event-driven architecture ensures that minigames can be seamlessly integrated with the tools, and be controlled through events and callbacks.

#### Example minigames include:
- Electrical Repair Minigame
- Terminal Hacking Minigame

## Features
- Modular tool interactions
- Customizable minigames
- Extensible architecture for adding new tools and interactions
- Event-driven architecture for seamless integration


## Example of Creating a New Tool
To create a new tool, follow these steps:
1. Create a new C++ class that inherits from the ToolBase class.
2. Implement the specific interaction logic for the new tool.
3. Create a new minigame class that defines the interactive sequence for the tool.
4. Link the new tool to the minigame using event-driven callbacks.

NewTool.h
```c++
// Example of a new tool class
UCLASS()
class TOOLSYSTEM_API ANewTool : public AToolBase // inherits from the base tool class
{
	GENERATED_BODY()
	
public:
    // it is optional if you don't want a widget for the minigame, you can skip this
	// UPROPERTY(EditDefaultsOnly, Category="ToolSystem | Tool")
	// TSubclassOf<class UMinigameWidgetBase> MinigameWidgetClass; 
	
	virtual void StartTool() override; // override the StartTool function to implement custom logic
	virtual void InitializeMinigame(UMinigameBase* minigame) override; // override to initialize the minigame
	
	virtual void OnMinigameStateChanged(EMinigameState NewState) override; // override to handle minigame state changes
	virtual void OnMinigameFinished(EMinigameState FinalState) override; // override to handle minigame completion
};
```

## Example of Creating a New Minigame
To create a new minigame, follow these steps:
1. Create a new C++ class that inherits from the MinigameBase class.
2. Implement the specific logic for the minigame.

NewMinigame.h
```c++
// Example of a new minigame class
UCLASS()
class TOOLSYSTEM_API UNewMinigame : public UMinigameBase // inherits from the base minigame class
{
	GENERATED_BODY()
	
protected:
	virtual void _StartMinigame() override; // override the _StartMinigame function to implement custom logic
};
```

## Event Flow

The Tool System uses an event-driven approach to communicate between tools and minigames.

Tools listen to minigame state changes and completion events to react accordingly.

### Example Event Handling in a Tool

```c++
void AToolBase::OnMinigameStateChanged(EMinigameState NewState)
{
	// Shared logic for all tools
}

void AToolBase::OnMinigameFinished(EMinigameState FinalState)
{
	// Shared completion logic
}
```

Child tools can override these events and optionally call the base implementation:

```c++
void ANewTool::OnMinigameFinished(EMinigameState FinalState)
{
	Super::OnMinigameFinished(FinalState); // Call base implementation

	// Tool-specific behavior
	if (FinalState == EMinigameState::Success)
	{
		// Apply tool effect
	}
}
```

## Minigame States

Minigames use a state-based flow to represent their current status during execution.

- **EMinigameState::NotStarted**  
  The minigame has not been started yet.

- **EMinigameState::InProgress**  
  The minigame is currently active and running.

- **EMinigameState::Success**  
  The minigame has been completed successfully.

- **EMinigameState::Failed**  
  The minigame has ended without success.

- **EMinigameState::Cancelled**  
  The minigame was cancelled before completion.




