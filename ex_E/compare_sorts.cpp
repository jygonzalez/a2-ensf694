/**
 *  File Name: compare_sorts.cpp
 *  Assignment: ENSF 694 Lab 2 Exercise E
 *  Created by: Mahmood Moussavi
 *  Completed by: Yael Gonzalez
 *  Submission Date: July 10, 2024
 */

#include "compare_sorts.h"

int main() {
    const char *input_file = "input.txt"; // Change this to your input file
    char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE];
    int num_words;
    
    read_words(input_file, words, num_words);
    
    int indices[num_words];
    for (int i = 0; i < num_words; ++i) {
        indices[i] = i;
    }

    sort_and_measure_quicksort(words, indices, num_words, quicksort, "Quick Sort");
    write_words("output_quicksort.txt", words, indices, num_words);
    sort_and_measure_shell_bubble(words, indices, num_words, shellsort, "Shell Sort");
    write_words("output_shellsort.txt", words, indices, num_words);
    sort_and_measure_shell_bubble(words, indices, num_words, bubblesort, "Bubble Sort");
    write_words("output_bubblesort.txt", words, indices, num_words);
    return 0;
}

void to_lower(char *str) {
    while (*str) {
        *str = std::tolower(*str);
        ++str;
    }
}

void strip_punctuation(char *word) {
    char *src_word = word;
    
    while (*src_word) {
        if(isalnum(*src_word) || *src_word == '-') {
            *word = *src_word;
            word++;
        }
        src_word++;
    }
    *word = '\0';
}

bool is_unique(char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int num_words, const char *word) {
    for (int i = 0; i < num_words; i++) {
        if (strcmp(words[i], word) == 0) {
            return false;
        }
    }
    return true;
}

void quicksort(int *indices, char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int left, int right) {
    if (left < right) {
        // Find the partitoin index (pi) such that:
        // - Elements smaller than pivot are on left of pivot
        // - Elements greater than pivot are on righ of pivot
        int pi = partition(indices, words, left, right);

        // Recursive call on the left of pi
        quicksort(indices, words, left, pi - 1);

        // Recursive call on the right of pi
        quicksort(indices, words, pi + 1, right);
    }
}

int partition(int *indices, char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int left, int right) {
    // Select the rightmost element as pivot
    int pivot = indices[right];
    
    // pointer for greater element
    int i = (left - 1);
    
    // traverse each element of the array
    // compare them with the pivot
    for (int j = left; j < right; j++) {
        if (strcmp(words[indices[j]], words[pivot]) <= 0) {  
            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;
            
            // swap element at i with element at j
            std::swap(indices[i], indices[j]);
        }
    }
    // swap pivot with the greater element at i
    std::swap(indices[i + 1], indices[right]);
    
    // return the partition point
    return (i + 1);
}

void shellsort(int *indices, char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int size) {
    // Start with a big gap, then reduce the gap
    for (int gap = size / 2; gap > 0; gap /= 2) {
        // Perform a gapped insertion
        for (int i = gap; i < size; i++) {
            int temp = indices[i];
            int j;
            for (j = i; j >= gap && strcmp(words[indices[j - gap]], words[temp]) > 0; j -= gap) {
                indices[j] = indices[j - gap];
            }
            indices[j] = temp;
        }
    }
}

void bubblesort(int *indices, char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            // Compare the words at the current indices
            if (strcmp(words[indices[j]], words[indices[j + 1]]) > 0) {
                // Swap the indices if out of order
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }
}

void read_words(const char *input_file, char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int &num_words) {
    std::ifstream infile(input_file);
    if (!infile) {
        std::cerr << "Error opening input file.\n";
        exit(1);
    }

    char word[MAX_WORD_SIZE + 1];
    num_words = 0;

    while (infile >> word) {
        strip_punctuation(word);
        to_lower(word);
        if (word[0] != '\0' && num_words < MAX_UNIQUE_WORDS && is_unique(words, num_words, word)) {
            std::strncpy(words[num_words++], word, MAX_WORD_SIZE);
        }
    }

    infile.close();
}

void write_words(const char *output_file, char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int *indices, int num_words) {
    std::ofstream outfile(output_file);
    if (!outfile) {
        std::cerr << "Error opening output file.\n";
        exit(1);
    }

    for (int i = 0; i < num_words; ++i) {
        outfile << words[indices[i]] << '\n';
    }

    outfile.close();
}

void sort_and_measure_quicksort(char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int* indices, int num_words, void (*sort_func)(int *, char [MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int, int), const char *sort_name) {
    const auto start_time = std::chrono::high_resolution_clock::now();   
    sort_func(indices, words, 0, num_words - 1);
    const auto end_time = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> time_diff = end_time - start_time;
    std::cout << "Sorting with " << sort_name << " completed in " << time_diff.count() << " seconds.\n";
}

void sort_and_measure_shell_bubble(char words[MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int* indices, int num_words, void (*sort_func)(int *, char [MAX_UNIQUE_WORDS][MAX_WORD_SIZE], int), const char *sort_name) {
    const auto start_time = std::chrono::high_resolution_clock::now();   
    sort_func(indices, words, num_words);
    const auto end_time = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> time_diff = end_time - start_time;
    std::cout << "Sorting with " << sort_name << " completed in " << time_diff.count() << " seconds.\n";
}
