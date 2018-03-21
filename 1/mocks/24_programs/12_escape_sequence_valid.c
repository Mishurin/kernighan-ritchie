// Still ok if ' or " appear without pair here in the comment
int main() {
    char a[] = 'abc';
    char b[] = "cb\aa";
    /*
        Same rule applies here: no error if ' or ""
    */
    return 0;
}