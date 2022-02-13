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
		static int ActionId;
		using FuncType = void (*)(Args...);
	public:
		std::vector<FuncType> functions;
		std::map<std::size_t, FuncType> dictOfAllFunctionsWithHash;
		std::map<int, std::vector<FuncType>> actionsDict;

	public:
		explicit Action()
		{
			ActionId++;
		}
		~Action()= default;

	private:
		std::size_t GetFunctionHash(void (*func)(Args...))
		{
			std::hash<void (*)(Args...)> funcHash;

			return funcHash(func);
		}

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
		void Invoke(const Args&... args)
		{
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

		void AddListener(void (*func)(Args...))
		{
			auto it0 = dictOfAllFunctionsWithHash.find(GetFunctionHash(func));

			if(it0 == dictOfAllFunctionsWithHash.end())
			{
				dictOfAllFunctionsWithHash.insert(std::pair<std::size_t, FuncType>(GetFunctionHash(func), func));
			}
			else
			{
				std::cout << "Function already added as a Listener!\n";
				return;
			}

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

		void RemoveListener(void (*func)(Args...))
		{
			auto it = dictOfAllFunctionsWithHash.find(GetFunctionHash(func));

			// If function is already registered
			// Then remove, the function from the list of that particular action's functions
			if(it != dictOfAllFunctionsWithHash.end())
			{
				for (auto k : actionsDict)
				{
					if(ActionId == k.first)
					{
						for (int i = 0; i < actionsDict[ActionId].size(); ++i)
						{
							if(GetFunctionHash(actionsDict[ActionId][i]) == GetFunctionHash(func))
							{
								actionsDict[ActionId].erase(actionsDict[ActionId].begin() + i);
							}
						}
					}
				}

				dictOfAllFunctionsWithHash.erase(GetFunctionHash(func));
			}
			else
			{
				std::cout << "Can't remove function which does not belong to this action.\n";
			}
		}
};

template<typename... Args>
int Action<Args...>::ActionId = -1;

#endif //GAMEENGINE_ACTION_H
