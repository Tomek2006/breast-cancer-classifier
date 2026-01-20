/**	file BinaryDecisionTree.h
	author : Tomek Marek
	date : 2025-12-12
	purpose: Establishes the binary logic for the Decision Tree node
*/

#include <vector>

//Setting up the class for the binary decision node
template<typename T>
class BinaryDecisionTree
{
public:
	using branch_logic_function = bool(*)(T&);
	using const_branch_logic_function = bool(*)(const T&);


protected:
	BinaryDecisionTree* true_branch_;
	BinaryDecisionTree* false_branch_;
	branch_logic_function logic_function_;
	const_branch_logic_function const_logic_function_;

	int leaf_result_;
	int is_leaf_;

public:
	BinaryDecisionTree(const branch_logic_function logic_func, BinaryDecisionTree* true_node = nullptr, BinaryDecisionTree* false_node = nullptr)
		:logic_function_(logic_func),
		const_logic_function_(nullptr), true_branch_(true_node), false_branch_(false_node)
		, leaf_result_(0), is_leaf_(false)
	{
	}

	BinaryDecisionTree(const const_branch_logic_function logic_func, BinaryDecisionTree* true_node = nullptr, BinaryDecisionTree* false_node = nullptr)
		: logic_function_(nullptr), const_logic_function_(logic_func), true_branch_(true_node), false_branch_(false_node)
		, leaf_result_(0), is_leaf_(false)
	{
	}

	BinaryDecisionTree(int result)
		: logic_function_(nullptr), const_logic_function_(nullptr),
		true_branch_(nullptr), false_branch_(nullptr),
		leaf_result_(result), is_leaf_(true)
	{
	}

	int classify(T& data);  

	~BinaryDecisionTree()
	{
	}
	bool process(T& data);
};
	
	template<typename T>
	inline bool BinaryDecisionTree<T>::process(T& data)
	{
		//call the linked functions
		bool result = false;
		if (logic_function_)
		{
			result = logic_function_(data);
		}
		else if (const_logic_function_)
		{
			result = const_logic_function_(data);
		}

		//use the result to see if we have anywhere to go next
		if (result)
		{
			if (true_branch_)
			{
				return true_branch_->process(data);
			}
		}
		else
		{
			if (false_branch_)
			{
				return false_branch_->process(data);
			}
		}

		//nowhere else to go, so return result of all to logic_function_(...)
		return result;
	}

	template <typename T>
	inline int BinaryDecisionTree<T>::classify(T& data) {
		if (is_leaf_) {
			return leaf_result_;
		}

		bool result = false;
		if (logic_function_) {
			result = logic_function_(data);
		}
		else if (const_logic_function_) {
			result = const_logic_function_(data);
		}


		if (result && true_branch_) {
			return true_branch_->classify(data);  
		}
		else if (!result && false_branch_) {
			return false_branch_->classify(data); 
		}

		return 0;
	}