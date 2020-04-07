#pragma once
#include <map>
#include <string>
#include <string_view>
#include <boost/tokenizer.hpp>
#include <functional>
#include "Defines.h"

BEGIN_NAMESPACE(RPNCalculator)
using t_string = std::string;
using t_string_view = std::string_view;
using separator = boost::char_separator<t_string::value_type>;
using tokenizer = boost::tokenizer<separator>;
using op_type = double;
using opmap = std::map<t_string, std::function<op_type(op_type, op_type)>>;


constexpr const char* Spaces = " \t";
constexpr const char* Operations = "+-*/^%";

template<typename Ty>
using remove_cvr_t = typename std::remove_cv<typename std::remove_reference<Ty>::type>::type;


template<class string_t>
inline bool Is_Value(const string_t& str)
{
	for (const auto ch : str) {
		if (!std::isdigit(ch) && ch != '.' && ch != 'x')
			return false;
	}
	return true;
}



template <typename T>
struct is_string {
	static constexpr bool value = false;
};

template <class T, class Traits, class Alloc>
struct is_string<std::basic_string<T, Traits, Alloc>>
{
	static constexpr bool value = true;
};

template <class T>
inline constexpr bool is_string_v = is_string<T>::value;




END_NAMESPACE(RPNCalculator)

