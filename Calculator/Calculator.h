#pragma once
#include <stack>
#include <type_traits>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/trim.hpp>

#include "Typedefs.h"
#include "Defines.h"



BEGIN_NAMESPACE(RPNCalculator)

class RPNCalculator
{
public:
	template<typename Iter,
		class = typename Iter::iterator_category,
		class = std::enable_if_t< is_string_v< typename Iter::value_type> >
	>
		op_type Calculate(Iter it, const Iter end);



	op_type Calculate(const t_string&);


private:
	op_type pop_stack();

	void do_operation(const t_string&);

	std::stack<op_type> values;

	static opmap operations;

};

template <class _Ty>
using remove_cvr = std::remove_cv_t<std::remove_reference_t<_Ty>>;


#ifdef USE_LEXICAL_CAST

template<typename Iter, class, class>
op_type RPNCalculator::Calculate(Iter it, const Iter end)
{
	static_assert(std::is_same_v<remove_cvr<decltype(*it)>, std::string>, "*it should be string type");
	for (; it != end; ++it) {
		try {
			values.push(boost::lexical_cast<op_type>(boost::trim_copy(*it)));
		}
		catch (const boost::bad_lexical_cast&) {//operation
			do_operation(*it);
		}
	}
	op_type result = pop_stack();
	BOOST_ASSERT_MSG(values.empty(), "Fatal Impl error, stack should'nt empty");
	return result;
}



#else
template<typename Iter>
op_type RPNCalculator::Calculate(Iter it, const Iter end)
{
	static_assert(std::is_same_v<remove_cvr<decltype(*it)>, std::string>, "*it should be string type");
	for (; it != end; ++it) {
		std::stringstream ss{ *it };
		if (op_type val; ss >> val) {
			values.push(val);
		}
		else {
			do_operation(*it);
		}
	}
	op_type result = pop_stack();
	BOOST_ASSERT_MSG(values.empty(), "Fatal Impl error, stack should'nt empty");
	return result;
}
#endif

END_NAMESPACE(RPNCalculator)

