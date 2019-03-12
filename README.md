# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

It's a 45 character word, the longest in the large dictionary.

## According to its man page, what does `getrusage` do?

It gives usage statistics for one of 3 options:
RUSAGE_SELF - for the calling process
RUSAGE_CHILDREN - for all descendants of the calling process that have terminated and been waited for
RUSAGE_THREAD - for the calling thread

## Per that same man page, how many members are in a variable of type `struct rusage`?

16 members

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

There's no need to create 2 additional local variables in calculate to receive copies of before and after. It would take more time because we would need to allocate additional memory to the stack and copy the current values of before and after. It would also take more memory temporarily.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

main uses fgetc to read characters one at a time from text, and it places them into an array called word. There are a few caveats. It only accepts values if they are alphabetical or apostrophes. If it receives a non-alphetetical, non-apostrophe, non-numeric character, it assumes the word has ended. This is probably a space or some punctuation in the text. The maximum word length is set to 45, so if main reads an alpha string longer than 45 characters, it assumes it is something other than a word, and it skips it. If main sees a numeric character in a word, it skips that word and does not count it.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

When looking for a string, fscanf might include words with punctuation or numeric characters in them. fgetc is able to catch these characters as they happen and skip the word if they appear. In order to catch these, you would need to iterate over each character in the word anyway, so you might as well read them in 1 char increments to begin with.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

We don't want check to change the value of the word array. We also don't want load to change the value of the dictionary array. We have to pass these arrays by pointer, which makes it possible for the check and load functions to alter the values of word and dictionary unless we specify const.
