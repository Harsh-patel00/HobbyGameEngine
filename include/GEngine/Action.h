//
// Created by Harsh on 12-02-2022.
//

#include <vector>
#include <map>
#include <iostream>
#include <functional>

#ifndef GAMEENGINE_ACTION_H
#define GAMEENGINE_ACTION_H

template<typename... Args>
class Action
{
	private:
		// Unique ActionID to identify every unique actions
		int ActionId;
		using FuncType = void (*)(Args...);
	public:
		// List of all registered function
		std::vector<FuncType> functions;
		// This maps every function with its hash (This way function is easier to find)
		std::map<std::size_t, FuncType> dictOfAllFunctionsWithHash;
		// This maps every function's list with its ActionID
		std::map<int, std::vector<FuncType>> actionsDict;

	public:
		// Whenever a new action is created, ActionID is incremented
		explicit Action()
		{
			ActionId++;
		}
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
		// This function is used to call all the methods that are subscribed/listening to a particular action
		void Invoke(const Args&... args)
		{
			// Only invoke functions of same action
			for (auto k : actionsDict)
			{
				if(ActionId == k.first)
				{
					for (int i = 0; i < actionsDict[ActionId].size(); ++i)
					{
						actionsDict[ActionId][i](args...);
					}
				}
			}
		}

		// Add a function as a listener to an Action
		void AddListener(void (*func)(Args...))
		{
			// Checking if the function is already a listener
			auto it0 = dictOfAllFunctionsWithHash.find(GetFunctionHash(func));

			// If not, get the hash and add it to the map
			if(it0 == dictOfAllFunctionsWithHash.end())
			{
				dictOfAllFunctionsWithHash.insert(std::pair<std::size_t, FuncType>(GetFunctionHash(func), func));
			}
			else
			{
				std::cout << "Function already added as a Listener!\n";
				return;
			}

			// Check if the action is already present
			auto it = actionsDict.find(ActionId);

			// If action is already registered
			// Then add, the function to the list of that particular action's functions
			if(it != actionsDict.end())
			{
				it->second.push_back(GetFunctionFromHash(GetFunctionHash(func)));
			}
			else // Add the action, and list of functions to the dictionary/map
			{
				functions.push_back(GetFunctionFromHash(GetFunctionHash(func)));
				actionsDict.template insert(std::pair<int, std::vector<void (*)(Args...)>>(ActionId, functions));
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
				for (auto k : actionsDict)
				{
					// Get the required Action from map
					if(ActionId == k.first)
					{
						for (int i = 0; i < actionsDict[ActionId].size(); ++i)
						{
							// Remove only the specified function from Action
							if(GetFunctionHash(actionsDict[ActionId][i]) == GetFunctionHash(func))
							{
								actionsDict[ActionId].erase(actionsDict[ActionId].begin() + i);
							}
						}
					}
				}

				// Remove the function from the map, as it's no longer a valid function
				dictOfAllFunctionsWithHash.erase(GetFunctionHash(func));
			}
			else
			{
				std::cout << "Can't remove function which does not belong to this action.\n";
			}
		}
};

#endif //GAMEENGINE_ACTION_H
