void get_identity(std::string my_id[]) {
  my_id[0] = "djbn65";
  my_id[1] = "12534397";
}

template <typename K, typename V>
MyMap<K,V>::MyMap() {
  root = nullptr; //empty tree
}

template <typename K, typename V>
MyMap<K,V>::~MyMap() {
  clear(); //clearing is synonymous to the destructor
}

template <typename K, typename V>
MyMap<K,V>::MyMap(const MyMap<K, V> &source) {
  root = clone(source.root); //make a new BST and return its root
}

template <typename K, typename V>
MyMap<K, V> & MyMap<K,V>::operator=(const MyMap<K, V> &source) {
  clear();
  root = clone(source.root); //make a new BST and return its root
  return *this;
}

template <typename K, typename V>
V & MyMap<K,V>::at(const K &key) {
  return at_helper(root, key);
}

template <typename K, typename V>
V & MyMap<K,V>::operator[](const K &key) {
  try
  {
    return at_helper(root,key);
  }
  catch(std::out_of_range &e) //if at_helper() throws exception node doesn't already exist, so insert it
  {
    insert(MyPair<K,V>(key));
    return at_helper(root,key);
  }
}

template <typename K, typename V>
bool MyMap<K,V>::empty() const {
  return !root; //if root points to null (0), list is empty, and it is not empty otherwise
}

template <typename K, typename V>
int MyMap<K,V>::size() const {
  return size_helper(root);
}

template <typename K, typename V>
void MyMap<K,V>::clear() {
  if (root != nullptr) //if no nodes, do nothing to avoid segfault
  {
    clear_helper(root);
    root = nullptr;
  }
  else
    return;
}

template <typename K, typename V>
void MyMap<K,V>::insert(const MyPair<K, V> &init_pair) {
  insert_helper(root, init_pair);
}

template <typename K, typename V>
void MyMap<K,V>::erase(const K &key) {
  if (empty()) //no possible nodes to erase, so return and do nothing
    return;
  else
    erase_helper(root, key);
}

template <typename K, typename V>
MyPair<K, V> * MyMap<K,V>::find(const K &key) const {
  return find_helper(root,key);
}

template <typename K, typename V>
void MyMap<K,V>::print() const {
  print_helper(root," ");
}

template <typename K, typename V>
int MyMap<K,V>::count(const K &key) const {
  return count_helper(root,key);
}

template <typename K, typename V>
V & MyMap<K,V>::at_helper(TreeNode<MyPair<K, V>> *&rt, const K &key) {
  if (rt == nullptr)
  {
    throw std::out_of_range("MyMap::at"); //node was not found, so throw out_of_range exception to be handled by other functions
  }

  if (rt->data.first == key) //key found, return value
    return rt->data.second;
  if (key < rt->data.first) //key is less than current node's key, so traverse left
    return at_helper(rt->left, key);
  else //key is greater than current node's key, so traverse right
    return at_helper(rt->right, key);
}

template <typename K, typename V>
int MyMap<K,V>::size_helper(TreeNode<MyPair<K, V>> *rt) const {
  int nodeCount = 0; //start nodecount at zero
  if (rt == nullptr) //if nullptr is encountered, tree/subtree is empty, so return zero
    return 0;
  nodeCount = nodeCount + 1 + size_helper(rt->left) + size_helper(rt->right); //recursively go down left and right subtrees, returning up the chain how many nodes
  return nodeCount;                                                           //there are in each subtree until the bottom is reached
}

template <typename K, typename V>
void MyMap<K,V>::clear_helper(TreeNode<MyPair<K, V>> *&rt) {
  TreeNode<MyPair<K, V>>* temp = rt;
  if (temp->left == nullptr && temp->right == nullptr) // a leaf is reached, so it can be deleted because no other nodes depend on its existence
  {
    delete temp;
    return;
  }
  if (temp->left != nullptr) //traverse down the left subtree recursively until base case is reached
    clear_helper(temp->left);
  if (temp->right != nullptr) //traverse down the right subree recursively until base case is reached
    clear_helper(temp->right);
  delete temp;
  return;
}

template <typename K, typename V>
void MyMap<K,V>::insert_helper(TreeNode<MyPair<K, V>> *&rt, const MyPair<K, V> &init_pair) {
  if (rt == nullptr)
    rt = new TreeNode<MyPair<K, V>>(init_pair, nullptr, nullptr); //spot to insert has been found so make new node
  else if (init_pair.first < rt->data.first) //go left if pair to insert's key is less than current key
    insert_helper(rt->left,init_pair);
  else if (init_pair.first > rt->data.first) //go right if pair to insert's key is greater than current key
    insert_helper(rt->right,init_pair);
  else //do nothing if key already exists
    return;
  return;
}

template <typename K, typename V>
TreeNode<MyPair<K, V>> * MyMap<K,V>::get_min(TreeNode<MyPair<K, V>> *rt) {
  if (empty()) //no possible min value if tree is empty
    return nullptr;
  if(rt->left == nullptr) //min value is found if this is the case. Tree has been traversed to left's end, so it is min
      return rt;
  else //traverse left until min value is found
      return get_min(rt->left);
}

template <typename K, typename V>
void MyMap<K,V>::erase_helper(TreeNode<MyPair<K, V>> *&rt, const K &key) {
  if (rt == nullptr) //base case, meaning key was not found, or the end of a branch was reached
    return;
  else if (key < rt->data.first) //traverse left if key is less than current key
    erase_helper(rt->left, key);
  else if (key > rt->data.first) //traverse right if key is greater than current key
    erase_helper(rt->right, key);
  else //key is found otherwise
  {
    TreeNode<MyPair<K, V>>* temp = rt; //keep a pointer to k,v pair to be removed so it's not lost
    if (rt->left == nullptr) //only a right child exists, so set rt to right child (this points the parent to this new rt node because of referenced pointer)
      rt = rt->right;
    else if (rt->right == nullptr) //only a left child exists, so set rt to left child (same reasoning above)
      rt = rt->left;
    else //node has two children
    {
      TreeNode<MyPair<K, V>>* min = get_min(rt->right); //make a pointer to minimum node in right subtree of node to be erased
      if (min->right == nullptr) //min val has no right children (impossible for it to have left children due to BST nature)
      {
        rt = new TreeNode<MyPair<K, V>>(min->data, temp->left, temp->right); //set rt to be same pointer as min found above, so parent now points to min
        if (temp->right == rt) //if min val in right subtree was the direct child of rt, set new right child to nullptr
          rt->right = nullptr;
        erase_helper(rt->right, min->data.first);
      }
      else //min val has a right subtree
      {
        rt = new TreeNode<MyPair<K, V>>(min->data, temp->left, temp->right);
        erase_helper(rt->right, min->data.first); //delete the min value found from the tree because it was used to replaced removed value
      }
    }
    delete temp; //remove the item wanted
  }
}

template <typename K, typename V>
MyPair<K, V> * MyMap<K,V>::find_helper(TreeNode<MyPair<K, V>> *rt, const K &key) const {
  if (rt == nullptr)
    return nullptr; //key was not found, so return nullptr
  if (key == rt->data.first)
    return &(rt->data); //key was found, so return a reference to the MyPair
  if (key < rt->data.first) //key to find is less than current key, so traverse left
    return find_helper(rt->left, key);
  else //key to find is greater than current key, so traverse right
    return find_helper(rt->right, key);
}

template <typename K, typename V>
void MyMap<K,V>::print_helper(TreeNode<MyPair<K, V>> *rt, std::string indent) const {
  if(rt == nullptr) //printer prints right to left a tree that displays top to bottom
                 //tree is sideways with the root at the far left
  {
    cout << indent << "  empty" << endl;
    return;
  }
  print_helper(rt->right, indent+="  "); //add more indent as tree moves right to show depth
  cout << indent << rt->data.first << " " << rt->data.second << endl;
  print_helper(rt->left, indent+=""); //as tree moves back left, do not add more indent
}

template <typename K, typename V>
int MyMap<K,V>::count_helper(TreeNode<MyPair<K, V>> *rt, const K &key) const {
  if (find_helper(rt,key) == nullptr) //if node not in tree, return 0
    return 0;
  else //otherwise return 1
    return 1;
}

template <typename K, typename V>
TreeNode<MyPair<K, V>> * MyMap<K,V>::clone(const TreeNode<MyPair<K, V>> *rt) {
  if (rt == nullptr)
    return nullptr; //return the nullptr when left and right children are null or whole tree is nullptr because empty
  return new TreeNode<MyPair<K, V>>(rt->data,clone(rt->left),clone(rt->right)); //recursively make a new tree using new tree nodes, returning root of new tree in the end
}
