#include <states/state_manager.h>

StateManager StateManager::instance;

StateManager::StateManager (void) 
{
	stack_.push(new InitialState());
	Log::add("PUSH/ :: initial state");
}

StateManager::~StateManager (void) {}

int StateManager::process (void)
{
	if (instance.stack_.size() >= 0)
	{
		State* current = instance.stack_.top();
		State* next = current -> process();

		if (current != next)
		{
			if (next == nullptr)
			{
				Log::add(std::string("POP :: ") + std::string(current->get_name()));
				instance.stack_.pop();

				if (instance.stack_.empty())
					return -1;
			}
			else
			{
				Log::add(std::string("PUSH :: ") + std::string(next->get_name()));
				instance.stack_.push(next);
			}
		}
	}

	return 0;
}	
