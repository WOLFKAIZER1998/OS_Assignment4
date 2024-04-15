// Ryan Delos Reyes; R642R993
// Homework 4: Page Replacement Algorithms


#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <sstream>

using namespace std;

// LRU Algorithm
int lru(const vector<int>& page_reference_string, int num_frames) {
    unordered_set<int> page_table;
    int page_faults = 0;

    for (int page : page_reference_string) {
        // If the page is not found in the page table, it's a page fault
        if (page_table.find(page) == page_table.end()) {
            // If there is still room in the memory, add the page
            if (page_table.size() < num_frames) {
                page_table.insert(page);
            }
            // Memory is full, replace the least recently used page
            else {
                int lru_page = *page_table.begin();
                page_table.erase(lru_page);
                page_table.insert(page);
                page_faults++;
            }
        }
        // Print the current state of the page table and the number of page faults
        cout << "Step " << page_faults + 1 << ": Page fault (" << page << ") - Page Table: {";
        for (const auto& p : page_table) {
            cout << p << ", ";
        }
        cout << "}, Frames: [" << page_table.size() << "], Faults: " << page_faults << endl;
    }

    return page_faults;
}

// Optimal Algorithm
int optimal(const vector<int>& page_reference_string, int num_frames) {
    unordered_set<int> page_table;
    vector<int> frames(num_frames, -1); // Vector to keep track of the pages in each frame
    int page_faults = 0;

    for (int i = 0; i < page_reference_string.size(); ++i) {
        int page = page_reference_string[i];
        // If the page is not found in the page table, it's a page fault
        if (page_table.find(page) == page_table.end()) {
            // If there is still room in the memory, add the page
            if (page_table.size() < num_frames) {
                frames[page_table.size()] = page;
                page_table.insert(page);
            }
            // If memory is full, find the page that will not be used for the longest time
            else {
                int farthest = i, idx;
                for (int j = 0; j < num_frames; ++j) {
                    int l;
                    for (l = i; l < page_reference_string.size(); ++l) {
                        if (frames[j] == page_reference_string[l]) {
                            if (l > farthest) {
                                farthest = l;
                                idx = j;
                            }
                            break;
                        }
                    }
                    if (l == page_reference_string.size()) {
                        idx = j;
                        break;
                    }
                }
                page_table.erase(frames[idx]);
                frames[idx] = page;
                page_table.insert(page);
                page_faults++;
            }
        }
        // Print the current state of the page table and the number of page faults
        cout << "Step " << i + 1 << ": Page fault(" << page << ") - Page Table : {";
        for (const auto& p : page_table) {
            cout << p << ", ";
        }
        cout << "}, Frames: [" << page_table.size() << "], Faults: " << page_faults << endl;
    }

    return page_faults;
}


// First In, First Out (FIFO) Algorithm
int fifo(const vector<int>& page_reference_string, int num_frames) {
    // Using queue to store pages in FIFO order
    queue<int> page_table;
    int page_faults = 0;

    for (int page : page_reference_string) {
        // If there is still room in the memory, add the page
        if (page_table.size() < num_frames) {
            page_table.push(page);
        }
        // If memory is full, remove the oldest page and add the new page
        else {
            int oldest_page = page_table.front();
            page_table.pop();
            page_table.push(page);
            page_faults++;
        }
        // Print the current state of the page table and the number of page faults
        cout << "Step " << page_faults + 1 << ": Page fault (" << page << ") - Page Table: {";
        queue<int> temp = page_table;

        while (!temp.empty())
        {
            cout << temp.front() << ", ";
            temp.pop();
        }
        cout << "}, Frames: [" << page_table.size() << "], Faults: " << page_faults << endl;
    }

    return page_faults;
}

int main() {
    vector<int> page_reference_string;
    int num_frames;
    string line;
    int page;

    // Ask the user for the pages in the reference string
    cout << "Enter the pages in the reference string (separated by spaces): ";
    getline(cin, line);
    istringstream iss(line);
    while (iss >> page) {
        page_reference_string.push_back(page);
    }

    // Ask the user for the number of frames
    cout << "Enter the number of frames: ";
    cin >> num_frames;

    cout << "---------------------------------------------------------------------------------" << endl;

    cout << "For LRU Algorithm:" << endl;
    cout << "Total Page Faults: " << lru(page_reference_string, num_frames) << endl << endl;

    cout << "For Optimal Algorithm:" << endl;
    cout << "Total Page Faults: " << optimal(page_reference_string, num_frames) << endl << endl;

    cout << "For FIFO Algorithm:" << endl;
    cout << "Total Page Faults: " << fifo(page_reference_string, num_frames) << endl << endl;

    return 0;
}