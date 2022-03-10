//
// Created by Harsh on 12-02-2022.
//

#include <map>
#include <iostream>

#ifndef GAMEENGINE_ACTION_H
#define GAMEENGINE_ACTION_H

template<typename... Args>
class Action
{
	private:
		using FuncType = void (*)(Args...);
	public:
		// This maps every function with its hash (This way function is easier to find)
		std::map<std::size_t, FuncType> dictOfAllFunctionsWithHash;

	public:
		// Whenever a new action is created, ActionID is incremented
		Action() = default;
		~Action()= default;

	private:
		// Create a function's hash
		std::size_t GetFunctionHash(void (*func)(Args...))
		{
			std::hash<void (*)(Args...)> funcHash;

			return funcHash(func);
		}

		// Get the function based on hash value from the dictionary/map
		FuncType GetFunctionFromHash(std::size_t funcHash)
		{
			auto it = dictOfAllFunctionsWithHash.find(funcHash);

			if(it != dictOfAllFunctionsWithHash.end())
			{
				return it->second;
			}
			else
			{
				std::cout << "No such function found in the dictionary!\n";
				return nullptr;
			}
		}

	public:
		// This function is used to call all the functions that are subscribed/listening to a particular action
		void Invoke(const Args&... args, const std::string& actionName)
		{
			if(dictOfAllFunctionsWithHash.empty())
			{
				std::cout << actionName << " has no functions to invoke\n";
				return;
			}

			auto dictCopy = dictOfAllFunctionsWithHash;

			// Invoke all functions which are registered
			for (auto item : dictCopy)
			{
				auto it = dictOfAllFunctionsWithHash.find(item.first);

				if(it != dictOfAllFunctionsWithHash.end())
				{
					item.second(args...);
				}
				else
				{
					std::cout << "Function you are trying to invoke is removed\n";
				}
			}
		}

		// Add a function as a listener to an Action
		void AddListener(void (*func)(Args...))
		{
			// Checking if the function is already a listener
			auto it = dictOfAllFunctionsWithHash.find(GetFunctionHash(func));

			// If not, get the hash and add it to the map
			if(it == dictOfAllFunctionsWithHash.end())
			{
				dictOfAllFunctionsWithHash.insert(std::pair<std::size_t, FuncType>(GetFunctionHash(func), func));
			}
			else
			{
				std::cout << "Function already added as a Listener!\n";
				return;
			}
		}

		// Remove the function as a listener of an Action
		void RemoveListener(void (*func)(Args...))
		{
			// Find the function in the map
			auto it = dictOfAllFunctionsWithHash.find(GetFunctionHash(func));

			// If function is already registered
			// Then remove, the function from the list of that particular action's functions
			if(it != dictOfAllFunctionsWithHash.end())
			{
				// Remove the function from the map, as it's no longer a valid function
				dictOfAllFunctionsWithHash.erase(GetFunctionHash(func));
				std::cout << "Function un-subscribed successfully\n";
			}
			else
			{
				std::cout << "Can't remove function which does not belong to this action.\n";
			}
		}
};

#endif //GAMEENGINE_ACTION_H
