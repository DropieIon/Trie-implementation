# Trie-implementation
This project aims to create a dictionary for efficient retrieval of data.
    
   There are 2 main trees in this program, one that stores the name of the books and one that stores the name of the authors. At the end of each final letter in a book/author name there is a pointer to another structure.
    In the books trie, it points to a structure called "Carte" (which is the romanian word for book). It contains information about the book, such as number of pages, a rating and the author. 
    In the authors trie, it points to a book trie that contains all the books that have been written by that specific author. 
    If the user decides to delete all the books written by an author, not only are the books in the book trie deleted, but the books in the book trie located at the end of the authors trie are deleted, as well as the author from the authros trie.
    
   Usage:
    
   The following commands can be placed in the input file (the "<>" characters are not needed):
    
    add_book <bookname>:<author>:<rating>:<number of pages> -> Adds a book to the books trie and the author in the authors trie
    
    search_book <title> -> Searches the book in the books trie and if it exists it prints the details to the output file, otherwise it just tells the user that the book doesn't exist.
    
    search_book <prefix_title>~ -> This command prints the frist 3 book titles that start with the prefix. If none are present, it outputs a message to the output file saying that no book has been found.
    
    list_author <author> -> Searches the author in the authors trie and prints out all of the books that have been written by the author in lexicological order. If the author isn't part of the trie, a message is given.
    
    list_author <author>~ -> This command is similar in functionality to the search_book autocomplete function.
    
    search_by_author <author>:<title> -> It is a similar command to the search_book command, but it searches in the authors trie. The output is similar to the search_book function. There is an error message present if the author isn't found.
    
    search_by_author <author>:<title_prefix>~ -> It does the same thing as the search_book with autocomplete, but it searches in the author trie first.
    
    delete_book <title> -> Deletes all information about the book from the authors trie, from the books trie and if the author has no more books in the dictionary, then the author is deleted from the authors trie.
    

The maximum number of characters allowed for the author name and book name is 50.
