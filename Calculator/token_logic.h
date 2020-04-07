#pragma once
#pragma once
#include <boost/token_functions.hpp>

//#pragma message("Please use the special functions assigned for qchar_separator!\
//Quotation's format is-> even indexes are opener quot marks,odd are close_quote's")


//#define keep_empty_toks_;
namespace token_function {
	///////////////////////////////////////////////////////////////////////////////////
	//Please use the special functions assigned for qchar_separator
	//Quotation's format is-> even indexes are opener quot marks,odd are close_quote's
	///////////////////////////////////////////////////////////////////////////////////
	constexpr const char* DefaultQuotes() {
		return"''[](){}\"\"<>";
	}

	template<typename Char,
		typename Tr = typename  std::basic_string<Char>::traits_type
	>
		class qchar_separator {
		using Traits = boost::tokenizer_detail::traits_extension<Tr>;
		using string_type = std::basic_string<Char, Tr>;

#if  _HAS_CXX17 || __cplusplus > 201701L
		using string_view = const std::basic_string_view<Char, Tr>;
#else
		using string_view = const string_type;
#endif
		public:
			explicit constexpr//strlen > sizeof(string_type) ? cxx20 : cxx20 & SSO
				qchar_separator(const Char* space_delims,
					const Char* punct_delims = "",
					const Char* quotations = ""
				) noexcept
				: m_spaces(space_delims),
				m_puncts(punct_delims),
				m_quotes(quotations)
			{
				assert(m_quotes.size() % 2 == 0);
			}

			void reset() noexcept { }

			template <typename InputIterator, typename Token>
			bool operator()(InputIterator& next, InputIterator end, Token& tok)
			{//operator ++ for InputIterator ???
				using assigner = boost::tokenizer_detail::assign_or_plus_equal<
					typename boost::tokenizer_detail::get_iterator_category<
					InputIterator
					>::iterator_category
				>;

				assigner::clear(tok);


				// skip past all space_delims
				for (; next != end && is_spaces(*next); ++next);

				InputIterator start(next);

				if (next == end)
					return false;

				// if we are on a punct_delims move past q and stop
				if (is_punct(*next)) {
					assigner::plus_equal(tok, *(next++));
				}
				else
					// append all the non delim characters
					for (; next != end && !is_spaces(*next) && !is_punct(*next) &&
						!is_quote(*next); assigner::plus_equal(tok, *(next++)));

				if (next == start && open_quote)
				{
					++next;
					size_t quoter_count = 1;
					while (quoter_count != 0) {
						for (; next != end && *next != close_quote; assigner::plus_equal(tok, *(next++)))
							if (*next == open_quote) ++quoter_count;
						if (next == end && quoter_count != 0)
							throw std::logic_error("invalid quotes");
						if (*next == close_quote) { --quoter_count; assigner::plus_equal(tok, *(next++)); }
					}


					//if (next != end && *next != close_quote)assigner::plus_equal(tok, *(next++));
					open_quote = false;
					close_quote = false;
				}

				assigner::assign(start, next, tok);
				return true;
			}

		private:

			string_view m_spaces;
			string_view m_puncts;
			string_view m_quotes;

			Char open_quote = '\000';
			Char close_quote = '\000';

			bool is_punct(Char E)const noexcept
			{
				if (!m_puncts.empty())
					return m_puncts.find(E) != string_type::npos;
				return false;
			}
			bool is_spaces(Char E) const noexcept
			{
				if (!m_spaces.empty())
					return m_spaces.find(E) != string_type::npos;
				return false;
			}

			bool is_quote(const Char E) noexcept {
				typename string_type::size_type q = string_type::npos;
				if (m_quotes.empty() || string_type::npos == (q = m_quotes.find(E))
					|| q % 2 == 1)
					return false;

				close_quote = m_quotes[q + 1];//q % 2 = 0
				open_quote = E;
				return true;
			}

	};//class qchar_separator

}//namespace tokenizer

