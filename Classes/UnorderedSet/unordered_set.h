#pragma once

#define ITERATOR_IMPLEMENTED
#define FORWARD_LIST_IMPLEMENTED

#include <forward_list>
#include <iostream>
#include <iterator>
#include <vector>

template <class KeyT>
size_t GetHash(const KeyT& value, const size_t& count_buckets) {
  return std::hash<KeyT>{}(value) % count_buckets;
}

template <class KeyT>
class UnorderedSet {
 public:
  using Iterator = typename std::forward_list<KeyT>::const_iterator;
  using ConstIterator = typename std::forward_list<KeyT>::const_iterator;
  using DifferenceType = std::ptrdiff_t;

 private:
  size_t count_elements_;
  size_t count_buckets_;
  std::vector<Iterator> buckets_;
  std::forward_list<KeyT> common_list_;

 public:
  Iterator begin() noexcept;             //  NOLINT
  ConstIterator begin() const noexcept;  //  NOLINT

  ConstIterator cbegin() const noexcept;  //  NOLINT
  ConstIterator cend() const noexcept;    //  NOLINT

  Iterator end() noexcept;             //  NOLINT
  ConstIterator end() const noexcept;  //  NOLINT

  [[nodiscard]] size_t Bucket(const KeyT& value) const noexcept;
  [[nodiscard]] size_t BucketCount() const noexcept;
  [[nodiscard]] size_t BucketSize(const size_t& hash) const noexcept;

  void Clear();

  [[nodiscard]] bool Empty() const noexcept;

  void Erase(const KeyT& value);

  bool Find(const KeyT& value) const noexcept;

  void Insert(const KeyT& value);
  void Insert(KeyT&& value);

  [[nodiscard]] double LoadFactor() const noexcept;

  void Rehash(const size_t& new_bucket_count);
  void Reserve(const size_t& new_bucket_count);

  [[nodiscard]] size_t Size() const noexcept;

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  UnorderedSet(Iterator first, Iterator second) {

    size_t count = 0;
    auto it = first;
    while (it != second) {
      ++count;
      ++it;
    }

    count_elements_ = count;
    count_buckets_ = count;
    buckets_.resize(count, Iterator());

    it = first;
    size_t hash = 0;
    if (count_elements_ != 0) {
      hash = GetHash(*it, count_buckets_);

      buckets_[hash] = common_list_.before_begin();
      common_list_.push_front(*it);

      ++it;
    }

    for (; it != second; ++it) {
      hash = GetHash(*it, count_buckets_);

      if (buckets_[hash] == Iterator()) {
        buckets_[hash] = common_list_.before_begin();
        common_list_.push_front(*it);

        auto second_element = std::next(common_list_.begin());
        buckets_[GetHash(*second_element, count_buckets_)] = common_list_.begin();
      } else {
        common_list_.insert_after(buckets_[hash], *it);
      }
    }
  }

  UnorderedSet();
  explicit UnorderedSet(const size_t& count);
  UnorderedSet(const UnorderedSet<KeyT>& other);
  UnorderedSet(UnorderedSet<KeyT>&& other) noexcept;

  UnorderedSet<KeyT>& operator=(const UnorderedSet<KeyT>& other);
  UnorderedSet<KeyT>& operator=(UnorderedSet<KeyT>&& other) noexcept;
};

template <class KeyT>
typename UnorderedSet<KeyT>::Iterator UnorderedSet<KeyT>::begin() noexcept {  //  NOLINT
  return common_list_.begin();
}

template <class KeyT>
typename UnorderedSet<KeyT>::ConstIterator UnorderedSet<KeyT>::begin() const noexcept {  //  NOLINT
  return common_list_.begin();
}

template <class KeyT>
typename UnorderedSet<KeyT>::ConstIterator UnorderedSet<KeyT>::cbegin() const noexcept {  //  NOLINT
  return common_list_.cbegin();
}

template <class KeyT>
typename UnorderedSet<KeyT>::ConstIterator UnorderedSet<KeyT>::cend() const noexcept {  //  NOLINT
  return common_list_.cend();
}

template <class KeyT>
typename UnorderedSet<KeyT>::Iterator UnorderedSet<KeyT>::end() noexcept {  //  NOLINT
  return common_list_.end();
}

template <class KeyT>
typename UnorderedSet<KeyT>::ConstIterator UnorderedSet<KeyT>::end() const noexcept {  //  NOLINT
  return common_list_.end();
}

template <class KeyT>
[[nodiscard]] size_t UnorderedSet<KeyT>::Bucket(const KeyT& value) const noexcept {
  return GetHash(value, count_buckets_);
}

template <class KeyT>
[[nodiscard]] size_t UnorderedSet<KeyT>::BucketCount() const noexcept {
  return count_buckets_;
}

template <class KeyT>
[[nodiscard]] size_t UnorderedSet<KeyT>::BucketSize(const size_t& hash) const noexcept {
  size_t size = 0;
  if ((count_elements_ != 0) && (hash < count_buckets_) && (buckets_[hash] != Iterator())) {
    for (auto it = std::next(buckets_[hash]); (it != common_list_.end()) && (GetHash(*it, count_buckets_) == hash);
         ++it) {
      ++size;
    }
  }
  return size;
}

template <class KeyT>
void UnorderedSet<KeyT>::Clear() {
  if (count_elements_ != 0) {
    size_t prev_hash = GetHash(*common_list_.begin(), count_buckets_);

    buckets_[prev_hash] = Iterator();
    common_list_.pop_front();

    size_t cur_hash = 0;
    for (auto& element : common_list_) {
      cur_hash = GetHash(element, count_buckets_);

      if (cur_hash != prev_hash) {
        buckets_[cur_hash] = Iterator();

        prev_hash = cur_hash;
      }
    }

    count_elements_ = 0;
    common_list_.clear();
  }
}

template <class KeyT>
bool UnorderedSet<KeyT>::Empty() const noexcept {
  return count_elements_ == 0;
}

template <class KeyT>
void UnorderedSet<KeyT>::Erase(const KeyT& value) {
  size_t hash = this->Bucket(value);

  if ((count_elements_ > 0) && (hash < count_buckets_) && (buckets_[hash] != Iterator())) {
    bool there_is = false;
    auto it = buckets_[hash];

    while ((std::next(it) != common_list_.end()) && (GetHash(*(std::next(it)), count_buckets_) == hash)) {

      if (*(std::next(it)) == value) {
        there_is = true;

        break;
      }

      ++it;
    }
    if (there_is) {
      size_t size = this->BucketSize(hash);

      if (size == 1) {
        buckets_[hash] = Iterator();
      }

      auto next_part_it = it;
      std::advance(next_part_it, 2);
      if ((next_part_it != common_list_.end()) && (GetHash(*next_part_it, count_buckets_) != hash)) {
        buckets_[GetHash(*next_part_it, count_buckets_)] = it;
      }

      common_list_.erase_after(it);
      --count_elements_;
    }
  }
}

template <class KeyT>
bool UnorderedSet<KeyT>::Find(const KeyT& value) const noexcept {
  bool there_is = false;

  if (count_elements_ != 0) {
    size_t hash = GetHash(value, count_buckets_);
    size_t size = this->BucketSize(hash);

    if (size != 0) {
      auto it_top_element = std::next(buckets_[hash]);

      while (size-- != 0) {
        if (*it_top_element == value) {
          there_is = true;

          break;
        }

        ++it_top_element;
      }
    }
  }

  return there_is;
}

template <class KeyT>
void UnorderedSet<KeyT>::Insert(const KeyT& value) {
  if (count_buckets_ != 0) {

    if (count_buckets_ == count_elements_) {
      Rehash(count_buckets_ * 2);
    }

    size_t new_hash = GetHash(value, count_buckets_);
    if (buckets_[new_hash] == Iterator()) {
      buckets_[new_hash] = common_list_.before_begin();
      common_list_.push_front(value);

      ++count_elements_;
      if (count_elements_ > 1) {
        auto second_element = std::next(common_list_.begin());
        buckets_[GetHash(*second_element, count_buckets_)] = common_list_.begin();
      }
    } else {
      common_list_.insert_after(buckets_[new_hash], value);

      ++count_elements_;
    }
  } else {
    this->Rehash(1);

    buckets_[0] = common_list_.before_begin();
    common_list_.push_front(value);

    ++count_elements_;
  }
}

template <class KeyT>
void UnorderedSet<KeyT>::Insert(KeyT&& value) {
  if (count_buckets_ != 0) {

    if (count_buckets_ == count_elements_) {
      Rehash(count_buckets_ * 2);
    }

    size_t new_hash = GetHash(value, count_buckets_);
    if (buckets_[new_hash] == Iterator()) {
      buckets_[new_hash] = common_list_.before_begin();
      common_list_.push_front(std::move(value));

      ++count_elements_;
      if (count_elements_ > 1) {
        auto second_element = std::next(common_list_.begin());
        buckets_[GetHash(*second_element, count_buckets_)] = common_list_.begin();
      }
    } else {
      common_list_.insert_after(buckets_[new_hash], std::move(value));

      ++count_elements_;
    }
  } else {
    this->Rehash(1);

    buckets_[0] = common_list_.before_begin();
    common_list_.push_front(std::move(value));

    ++count_elements_;
  }
}

template <class KeyT>
[[nodiscard]] double UnorderedSet<KeyT>::LoadFactor() const noexcept {
  double load_factor = 0.;
  if (count_buckets_ != 0) {
    load_factor = static_cast<double>(count_elements_) / count_buckets_;
  }

  return load_factor;
}

template <class KeyT>
void UnorderedSet<KeyT>::Rehash(const size_t& new_bucket_count) {
  if (new_bucket_count >= count_elements_) {

    if (count_elements_ != 0) {
      std::forward_list<KeyT> new_list;
      buckets_.clear();
      buckets_.resize(new_bucket_count, Iterator());
      buckets_.shrink_to_fit();
      count_buckets_ = new_bucket_count;

      size_t new_hash = 0;
      size_t tmp_size = 0;
      while (common_list_.begin() != common_list_.end()) {
        new_hash = GetHash(*common_list_.begin(), count_buckets_);

        if (buckets_[new_hash] == Iterator()) {
          new_list.splice_after(new_list.before_begin(), common_list_, common_list_.before_begin(),
                                std::next(common_list_.begin()));
          buckets_[new_hash] = new_list.before_begin();

          ++tmp_size;
          if (tmp_size > 1) {
            auto second_element = std::next(new_list.begin());
            buckets_[GetHash(*second_element, count_buckets_)] = new_list.begin();
          }
        } else {
          new_list.splice_after(buckets_[new_hash], common_list_, common_list_.before_begin(),
                                std::next(common_list_.begin()));

          ++tmp_size;
        }
      }
      buckets_[GetHash(*new_list.begin(), count_buckets_)] = common_list_.before_begin();
      common_list_.splice_after(common_list_.before_begin(), new_list, new_list.before_begin(), new_list.end());
    } else {
      buckets_.clear();
      buckets_.resize(new_bucket_count, Iterator());
      buckets_.shrink_to_fit();
      count_buckets_ = new_bucket_count;
    }
  }
}

template <class KeyT>
void UnorderedSet<KeyT>::Reserve(const size_t& new_bucket_count) {
  if (new_bucket_count > count_buckets_) {
    if (count_elements_ != 0) {
      std::forward_list<KeyT> new_list;
      buckets_.clear();
      buckets_.resize(new_bucket_count, Iterator());
      buckets_.shrink_to_fit();
      count_buckets_ = new_bucket_count;

      size_t new_hash = 0;
      size_t tmp_size = 0;
      while (common_list_.begin() != common_list_.end()) {
        new_hash = GetHash(*common_list_.begin(), count_buckets_);

        if (buckets_[new_hash] == Iterator()) {
          new_list.splice_after(new_list.before_begin(), common_list_, common_list_.before_begin(),
                                std::next(common_list_.begin()));
          buckets_[new_hash] = new_list.before_begin();

          ++tmp_size;
          if (tmp_size > 1) {
            auto second_element = std::next(new_list.begin());
            buckets_[GetHash(*second_element, count_buckets_)] = new_list.begin();
          }
        } else {
          new_list.splice_after(buckets_[new_hash], common_list_, common_list_.before_begin(),
                                std::next(common_list_.begin()));

          ++tmp_size;
        }
      }
      buckets_[GetHash(*new_list.begin(), count_buckets_)] = common_list_.before_begin();
      common_list_.splice_after(common_list_.before_begin(), new_list, new_list.before_begin(), new_list.end());
    } else {
      buckets_.clear();
      buckets_.resize(new_bucket_count, Iterator());
      buckets_.shrink_to_fit();
      count_buckets_ = new_bucket_count;
    }
  }
}

template <class KeyT>
size_t UnorderedSet<KeyT>::Size() const noexcept {
  return count_elements_;
}

template <class KeyT>
UnorderedSet<KeyT>::UnorderedSet() : count_elements_(0), count_buckets_(0), buckets_(), common_list_() {
}

template <class KeyT>
UnorderedSet<KeyT>::UnorderedSet(const size_t& count)
    : count_elements_(0), count_buckets_(count), buckets_(count, Iterator()), common_list_() {
}

template <class KeyT>
UnorderedSet<KeyT>::UnorderedSet(const UnorderedSet<KeyT>& other)
    : count_elements_(other.count_elements_), count_buckets_(other.count_buckets_) {
  buckets_.resize(count_buckets_, Iterator());

  auto it = other.begin();
  size_t hash = 0;
  if (count_elements_ != 0) {
    hash = GetHash(*it, count_buckets_);

    buckets_[hash] = common_list_.before_begin();
    common_list_.push_front(*it);

    ++it;
  }

  for (; it != other.end(); ++it) {
    hash = GetHash(*it, count_buckets_);

    if (buckets_[hash] == Iterator()) {
      buckets_[hash] = common_list_.before_begin();
      common_list_.push_front(*it);

      auto second_element = std::next(common_list_.begin());
      buckets_[GetHash(*second_element, count_buckets_)] = common_list_.begin();
    } else {
      common_list_.insert_after(buckets_[hash], *it);
    }
  }
}

template <class KeyT>
UnorderedSet<KeyT>::UnorderedSet(UnorderedSet<KeyT>&& other) noexcept
    : count_elements_(other.count_elements_), count_buckets_(other.count_buckets_) {

  buckets_ = std::move(other.buckets_);
  buckets_[GetHash(*other.begin(), count_buckets_)] = common_list_.before_begin();

  common_list_.splice_after(common_list_.before_begin(), other.common_list_, other.common_list_.before_begin(),
                            other.end());

  other.count_elements_ = 0;
  other.count_buckets_ = 0;
}

template <class KeyT>
UnorderedSet<KeyT>& UnorderedSet<KeyT>::operator=(const UnorderedSet<KeyT>& other) {
  this->Clear();
  buckets_.resize(other.BucketCount(), Iterator());
  count_buckets_ = other.count_buckets_;
  count_elements_ = other.count_elements_;

  auto it = other.begin();
  size_t hash = 0;
  if (count_elements_ != 0) {
    hash = GetHash(*it, count_buckets_);

    buckets_[hash] = common_list_.before_begin();
    common_list_.push_front(*it);

    ++it;
  }

  for (; it != other.end(); ++it) {
    hash = GetHash(*it, count_buckets_);

    if (buckets_[hash] == Iterator()) {
      buckets_[hash] = common_list_.before_begin();
      common_list_.push_front(*it);

      auto second_element = std::next(common_list_.begin());
      buckets_[GetHash(*second_element, count_buckets_)] = common_list_.begin();
    } else {
      common_list_.insert_after(buckets_[hash], *it);
    }
  }

  return *this;
}

template <class KeyT>
UnorderedSet<KeyT>& UnorderedSet<KeyT>::operator=(UnorderedSet<KeyT>&& other) noexcept {
  count_buckets_ = other.count_buckets_;
  count_elements_ = other.count_elements_;

  buckets_ = std::move(other.buckets_);

  common_list_.clear();
  buckets_[GetHash(*other.begin(), count_buckets_)] = common_list_.before_begin();
  common_list_.splice_after(common_list_.before_begin(), other.common_list_, other.common_list_.before_begin(),
                            other.end());

  other.count_buckets_ = 0;
  other.count_elements_ = 0;

  return *this;
}