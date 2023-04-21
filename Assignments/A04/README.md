
## A04 - Assignment A04 - Presentations
### Madhav Adhikari
### Description:
Knuth-Morris-Pratt Algorithm
•	What is the KMP Algorithm?
The KMP Algorithm is a string-matching algorithm used to find occurrences of a pattern within a longer text string. It was invented by Donald Knuth, James H. Morris, and Vaughan Pratt in 1977.

•	How does the KMP Algorithm work?
	The KMP Algorithm uses a prefix function to preprocess the pattern to identify any suffixes that match any prefixes of the pattern.
	This information is used to avoid unnecessary character comparisons during the matching process, making it more efficient.
	The algorithm matches the pattern against the text string by sliding the pattern over the text string, comparing characters until a match is found or the end of the text string is reached.

•	What is the time complexity and space complexity of the KMP Algorithm?
The KMP Algorithm has a time complexity of O(n + m) and space complexity O(m), where n is the length of the text string and m is the length of the pattern.

•	What are the advantages of the KMP Algorithm?
The KMP Algorithm is faster than other string matching algorithms, such as the Naive Algorithm.It is particularly useful for large inputs and is widely used in various applications, such as text editors, compilers, and bioinformatics.

•	What are the steps involved in implementing the KMP Algorithm?
	Preprocess the pattern to compute the prefix function.
	Slide the pattern over the text string and compare characters.
	If a match is found, continue matching from the next character in the text string.
	If no match is found, use the prefix function to determine how far to slide the pattern.


•	Example:
Suppose we want to find all occurrences of the pattern "abc" in the text string "abababcababc".
The KMP Algorithm preprocesses the pattern to compute the prefix function: pi = [0, 0, 0].
The algorithm then slides the pattern over the text string, comparing characters until a match is found at position 6. Since a match is found, the algorithm continues matching from the next character in the text string. When the end of the text string is reached, the algorithm has found all occurrences of the pattern "abc".


### Files

|   #   | File            | Description                                        |
| :---: | --------------- | -------------------------------------------------- |
|   1   | Hand_out_knuth-morris-pratt (kmp) algorithm.docx       | handsout   |
|   2   | knuth-morris-pratt (kmp) algorithm ppt.pptx | Presentations slides  |


### Instructions

-None for now

### Example Command:
- None for now
