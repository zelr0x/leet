#include <random>
#include <unordered_map>
#include <vector>

class RandomizedSet {
public:
    RandomizedSet() : gen(std::random_device{}()) {
        elem.reserve(CAP);
        indices.reserve(CAP);
    }

    bool insert(int val) {
        auto res = indices.emplace(val, elem.size());
        if (res.second) {
            elem.push_back(val);
            return true;
        }
        return false;
    }

    bool remove(int val) {
        auto it = indices.find(val);
        if (it == indices.end()) return false;
        size_t remIdx = it->second;
        if (remIdx != elem.size() - 1) {
            int last = elem.back();
            elem[remIdx] = last;
            indices[last] = remIdx;
        }
        indices.erase(val);
        elem.pop_back();
        return true;
    }

    int getRandom() {
        if (!elem.size()) throw std::runtime_error("The set is empty");
        std::uniform_int_distribution<size_t> dist(0, elem.size() - 1);
        size_t i = dist(gen);
        return elem[i];
    }

private:
    std::unordered_map<int, size_t> indices;
    std::vector<int> elem;
    std::mt19937_64 gen;

    static constexpr size_t CAP = 512;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */