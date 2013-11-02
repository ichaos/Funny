//LRU cache
//cache unit T must support key and value
#include <map>
#include <list>

template <typename T, typename TKey>
class LRUCache {
	std::map<TKey, T> cache;
	int capacity;
	int size;
	std::list<TKey> ll;

public:
	bool get(TKey k, T &t) {
		bool find = true;
		if (cache.find(k) == cache.end())
			return false;

		//promote
		ll.erase(k);
		ll.push_back(k);
		t = cache[k];
		return true;
	}

	void set(TKey k, T &t) {
		if (size < capacity) {
			ll.push_back(k);
			cache[k] = t;
			size++;
		} else {
			//prune
			TKey rm = ll.front();
			ll.pop_front();
			ll.push_back(k); 
			cache.erase(rm);

			cache[k] = t;
		}
	}

	LRUCache(int cap) : capacity(cap), size(0) {}
	LRUCache() : capacity(1024), size(0) {}
};