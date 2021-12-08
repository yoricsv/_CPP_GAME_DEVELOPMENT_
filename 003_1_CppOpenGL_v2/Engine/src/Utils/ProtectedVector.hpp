//
// Created by Андрей Марцинкевич on 02.02.18.
//

#pragma once


#include <vector>
#include <set>
#include <unordered_set>

	template<typename T>
	class ProtectedVector
	{
	public:
	    ProtectedVector() = default;
	    ProtectedVector(const ProtectedVector& ) = delete;
	    ProtectedVector(ProtectedVector&&) = default;

		void add(const T& t);
		void add(T&& t);

		void remove(const T& t);

		template<typename PRED>
		void removeIf(PRED pred);

		template<typename FUN>
		void forEach(FUN fun);

	private:
		void addData();
		void removeData();

		std::vector<T>              _data;
		std::vector<T>              _dataToAdd;
		std::unordered_set<size_t>  _dataToRemove;

		bool _isUpdate = false;
	};


    template<typename T>
    template <typename FUN>
    inline void ProtectedVector<T>::forEach(FUN fun)
    {
        _isUpdate = true;

        int i = 0;
        for (auto& item : _data)
        {
            fun(item);
        }

        _isUpdate = false;

        this->removeData();
        this->addData();
    }

    template<typename T>
    inline void ProtectedVector<T>::addData()
    {
        for (auto&& t : _dataToAdd)
        {
            _data.push_back(std::move(t));
        }

        _dataToAdd.clear();
    }

    template<typename T>
    inline void ProtectedVector<T>::removeData()
    {
        if (!_dataToRemove.empty())
        {
            std::vector<T> _newData;

            for (size_t i = 0; i < _data.size(); ++i)
            {
                if (_dataToRemove.find(i) == _dataToRemove.end())
                {
                    _newData.push_back(std::move(_data[i]));
                }
            }

            _data = std::move(_newData);

            _dataToRemove.clear();
        }
    }



    template<typename T>
	inline void ProtectedVector<T>::add(const T& t)
	{
		if (_isUpdate)
		{
			_dataToAdd.push_back(t);
		}
		else
		{
			_data.push_back(t);
		}
	}

	template<typename T>
	inline void ProtectedVector<T>::add(T&& t)
	{
		if (_isUpdate)
		{
			_dataToAdd.emplace_back(std::move(t));
		}
		else
		{
			_data.emplace_back(std::move(t));
		}
	}

	template<typename T>
	inline void ProtectedVector<T>::remove(const T& t)
	{
		if (_isUpdate)
		{
            auto it = std::find(_data.begin(), _data.end(), t);
            auto index = static_cast<const size_t>(std::distance(_data.begin(), it));
			_dataToRemove.insert(index);
		}
		else
		{
			auto it = std::remove(_data.begin(), _data.end(), t);
			if (it != _data.end())
			{
				_data.erase(it);
			}
		}
	}


	template<typename T>
	template<typename PRED>
	inline void ProtectedVector<T>::removeIf(PRED pred)
	{
        if (_isUpdate)
        {
            for (size_t i = 0; i < _data.size(); ++i)
            {
                if (pred(_data[i]))
                {
                    _dataToRemove.insert(i);
                }
            }
        }
        else
        {
	        auto it = std::remove_if(_data.begin(), _data.end(), pred);
	        if (it != _data.end())
	        {
		        _data.erase(it);
	        }
        }
	}
