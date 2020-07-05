#include <iostream>
#include <list>
#include <unordered_map>
#include <mutex>

using namespace std;

class LRUCache final {
 public:
  LRUCache(int capacity);  
  ~LRUCache() = default;
  
  void put(int key, int value);
  int get(int key);
  bool isFull();

  void print(); //按LRU顺序打印
  void show_map();
 private:
  int capacity_;
  int size_;
  mutex mutex_;
  list<pair<int, int>> list_cache_; //key, value
  unordered_map<int, list<pair<int, int>>::iterator> map_;  //key, 链表迭代器
};

LRUCache::LRUCache(int capacity)
    : capacity_(capacity), size_(0) {}

bool LRUCache::isFull() {
    return (size_ == capacity_ ? true : false); 
}

int LRUCache::get(int key) {
    //找map_，找得到，将list 对应节点头插,并更新节点的位置信息到map，找不到返回-1
    lock_guard<mutex> lk(mutex_);
    auto it = map_.find(key);
    if (it == map_.end())
        return -1;

    auto kv = *it->second; //先保存kv值
    list_cache_.erase(it->second);
    list_cache_.push_front(kv); 
    map_[key] = list_cache_.begin();
    
    return kv.second;
}

void LRUCache::put(int key, int value) {
    //先判断是否存在，存在则更新list信息、然后头插，最后更新map节点的位置信息;
    //不存在则判断LRUCache是否已满，已满则删除map对应节点, 然后pop_back list最后（oldest）节点,
    //最后list头插节点,map保存key值和节点位置信息
    lock_guard<mutex> lk(mutex_);
    auto it = map_.find(key);
    if (it != map_.end()) {
        auto kv = *it->second;//先保存kv值
        list_cache_.erase(it->second);
        kv.second = value;
        list_cache_.push_front(kv);
        map_[key] = list_cache_.begin();
    } else {
        if (isFull()) {
            map_.erase(list_cache_.back().first); 
            list_cache_.pop_back();
            size_--;
        } 
        auto kv = make_pair(key, value);
        list_cache_.push_front(kv);
        map_[key] = list_cache_.begin();
        size_++; //自增
    }
}

void LRUCache::print() {
    lock_guard<mutex> lk(mutex_);
    for (auto kv : list_cache_) {
        cout<<kv.first<<":"<<kv.second<<endl;
    }
}

void LRUCache::show_map()
{
    lock_guard<mutex> lk(mutex_);
    for (auto i : map_) {
       cout<<i.first<<endl;
    }
}


int main()
{
    LRUCache* lru_cache = new LRUCache(3);
    lru_cache->put(1, 11);
    lru_cache->put(2, 22);
    lru_cache->put(3, 33);
    lru_cache->print(); //此时3:33最先输出
    cout<<endl;
    
    lru_cache->put(2, 222);
    lru_cache->print(); //此时 2:222最先输出
    cout<<endl;
    
    lru_cache->put(4, 44);
    lru_cache->print(); //此时Cache已满，1:11被淘汰，不再输出
    cout<<endl;
    
    lru_cache->get(2);
    lru_cache->print(); //时候2:222会最先输出
    cout<<endl;

    cout<<lru_cache->get(5)<<endl; //找不到返回 -1
 
    return 0;
}






