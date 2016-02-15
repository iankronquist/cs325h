class Tree:
    def __init__(self, value, left=None, right=None):
        self.left = left
        self.right = right
        self.value = value

    def __str__(self):
        return '{}{}{}'.format(self.left or '', self.right or '', self.value)

    def print_tree(self):
        left_part = self.left.print_tree() if self.left else ""
        right_part = self.right.print_tree() if self.right else ""
        return left_part + right_part + self.value

def tree_recovery(pre, post):
    if len(pre) == 1:
        return Tree(pre[0])
    elif len(pre) == 0:
        return None
    i = 0
    root = pre[0]
    for i, item in enumerate(post):
        if item == root:
            break
    left = tree_recovery(pre[1:i+1], post[:i])
    right = tree_recovery(pre[i+1:], post[i+1:])
    n = Tree(root, left, right)
    return n

if __name__ == '__main__':
    t = tree_recovery("DBACEGF", "ABCDEFG")
    print(t)
