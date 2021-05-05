#pragma once

#include <vector>

/*
	Une extension de std::vector pour multiplier
	la capacit� par 2 � chaque fois que la taille
	d�passe la capacit�.
	Cette extension permet d'�viter de r�allouer
	tout le vecteur � chaque nouvel �l�ment ins�r�.
*/
template<typename T>
class BetterVector: public std::vector<T>
{
	using std::vector<T>::vector;

public:
	void push_back(const T& value)
	{
		size_t cap = std::vector<T>::capacity();

		if (cap <= std::vector<T>::size())
			std::vector<T>::reserve(2 * cap);

		std::vector<T>::push_back(value);
	}

	void push_back(T&& value)
	{
		size_t cap = std::vector<T>::capacity();

		if (cap <= std::vector<T>::size())
			std::vector<T>::reserve(2 * cap);

		std::vector<T>::push_back(std::move(value));
	}

	template<typename... Args>
	T& emplace_back(Args&&... args)
	{
		size_t cap = std::vector<T>::capacity();

		if (cap <= std::vector<T>::size())
			std::vector<T>::reserve(2 * cap);

		std::vector<T>::emplace_back(std::forward<Args>(args)...);
		return std::vector<T>::back();
	}
};