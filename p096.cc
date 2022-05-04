// Solver for the 9x9 Sudoku
// Adapted from a solver written in 2008.

#include <cstdio>
#include <vector>
#include <iostream>
#include <cstring>
#include <limits>

using namespace std;

struct node {
  int size, name;
  node *left, *right, *up, *down, *top;
  node(): size(0) {}
};

typedef std::vector<bool> vb;
typedef std::vector<vb> vvb;

template<typename T>
struct _exactcover {
  int w, h;
  T& callback;
  std::vector<int> solution;
  node *root;

  _exactcover(const vvb& mat, T& callback_)
      : w(mat[0].size()), h(mat.size()), callback(callback_)
  {
    root = getnode();
    root->left = root;
    root->right = root;
    root->name = -1000000;
    std::vector<node*> head(w);
    for (int i = 0; i < w; i++) {
      node* next = head[i] = getnode();
      next->right = root;
      next->left = root->left;
      root->left = next;
      next->left->right = next;
      next->up = next;
      next->down = next;
      next->name = -i-1;
    }
    for (int i = 0; i < h; i++) {
      node* root = NULL;
      for (int j = 0; j < w; j++) {
        if (mat[i][j]) {
          node* current;
          if (root == NULL) {
            current = root = getnode();
            root->left = root;
            root->right = root;
          } else {
            node* next = current = getnode();
            next->right = root;
            next->left = root->left;
            root->left = next;
            next->left->right = next;
          }
          current->down = head[j];
          current->up = head[j]->up;
          head[j]->up = current;
          current->up->down = current;
          current->top = head[j];
          current->name = i;
          head[j]->size++;
        }
      }
    }
  }

  ~_exactcover() {
    for (node* i = root->right; i != root;) {
      for (node* j = i->down; j != i;) {
        j = j->down;
        delete j->up;;
      }
      i = i->right;
      delete i->left;
    }
    delete root;
  }

  node* getnode() {
    return new node;
  }

  void cover(node* col) {
    col->right->left = col->left;
    col->left->right = col->right;
    for (node* i = col->down; i != col; i = i->down) {
      for (node* j = i->right; j != i; j = j->right) {
        j->down->up = j->up;
        j->up->down = j->down;
        j->top->size--;
      }
    }
  }

  void uncover(node* col) {
    for (node* i = col->up; i != col; i = i->up) {
      for (node* j = i->left; j != i; j = j->left) {
        j->top->size++;
        j->up->down = j;
        j->down->up = j;
      }
    }
    col->right->left = col;
    col->left->right = col;
  }

  void solve(void) {
    if (root->right == root) {
      callback(solution);
      return;
    }

    int minvalue = std::numeric_limits<int>::max();
    node* mincol = root;
    for (node* n = root->right; n != root; n = n->right) {
      if (n->size < minvalue) {
        minvalue = n->size;
        mincol = n;
      }
    }
    if (minvalue == 0)
      return;

    cover(mincol);
    for (node* r = mincol->down; r != mincol; r = r->down) {
      for (node* j = r->right; j != r; j = j->right)
        cover(j->top);
      solution.push_back(r->name);
      solve();
      solution.pop_back();
      for (node* j = r->left; j != r; j = j->left)
        uncover(j->top);
    }
    uncover(mincol);
  }

};

template<class T>
void exactcover(const vvb& mat, T& callback) {
  _exactcover<T> cover(mat, callback);
  cover.solve();
}

// callback to sum the solutions found.
struct eval_solution {
  int total = 0;
  void operator()(const vector<int>& solution) {
    char tab[9][9];
    memset(tab, 0, sizeof tab);
    for (auto it : solution)
      tab[it / 9 / 9][it / 9 % 9] = 1 + it % 9;
    int code = tab[0][0] * 100 + tab[0][1] * 10 + tab[0][2];
    total += code;
  }
};

int main(void) {
  eval_solution solution;

  for (string grid, number; cin >> grid >> number; ) {
    // read the grid from stdin.
    char given[9][9];
    string line;
    for (int j = 0; j < 9; j++) {
      cin >> line;
      for (int i = 0; i < 9; i++) {
        given[j][i] = line[i] - '1';
      }
    }

    // build the exact cover matrix.
    vvb mat(9*9*9, vb(9*9*4, false));
    for (int digit = 0; digit < 9; digit++)
      for (int row = 0; row < 9; row++)
        for (int col = 0; col < 9; col++) {
          if (given[row][col] >= 0 && given[row][col] != digit)
            continue;
          int i = digit + col*9 + row*9*9;
          mat[i][col + row*9] = true;
          mat[i][9*9 + row*9 + digit] = true;
          mat[i][9*9*2 + col*9 + digit] = true;
          int box = (row / 3) * 3 + col / 3;
          mat[i][9*9*3 + box*9 + digit]=true;
        }

    // print the solution.
    exactcover(mat, solution);
  }

  cout << solution.total << "\n"; 

  return 0;
}
