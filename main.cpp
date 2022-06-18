#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'pageCount' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER p
 */

int pageCount(int numberOfPages, int desiredPage) {
    vector <int> book;
    int minPagesTurned = 0;
    bool lastPageBlank = false;
    int blankPage = 404;
    int forwardPagesFlipped = 0;
    int reversePagesFlipped = 0;
    int currentPage = 0;
    int nextPage = 0;
    int prevPage = 0;
    bool pageFound = false;
    bool endOfBook = false;
    bool beginningOfBook = false;

    // if numberOfPages (with an index of 0) is divisible by 2, there must be a "blank page" at the end of the book.
    if ((numberOfPages % 2) == 0 ) {
        lastPageBlank = true;
    }

    // if (lastPageBlank), vectorSize (of index 0) must be numberOfPages + 1.
    // The plus one is the blank page at the back.

    //Create a vector of book [zero index] with of either size n or n+1
    for (int i = 0; i <= numberOfPages; i++) {
        if (i == 0) {
            book.push_back(0); //Page 0 is always blank.
        }

        if (i != 0) {
            if (!lastPageBlank) {
                book.push_back(i); //Pushing all pages from 1 to n
            }
            else {
                if ( i != numberOfPages) {
                    book.push_back(i); //Pushing all pages from 1 to (n-1) if last page should be blank.
                }
            }
        }

        if (lastPageBlank) {
            if (i == numberOfPages) {
                book.push_back(i); //Last real page
                book.push_back(blankPage); //Add blank page at the end
            }
        }
    }

    //Starting at the front of the book:
    //set index to front, check if the page being looked for is either i or i+1.
    // If not, flip through pages 2 at a time. incrementing a pagedFlipped counter.

    while ((!pageFound) && (!endOfBook) ) {
        nextPage = book[currentPage + 1];
        if (nextPage == 404) {
            endOfBook = true;
        }
        if (currentPage == desiredPage || nextPage == desiredPage) {
            pageFound = true;
        }
        else {
            forwardPagesFlipped++;
            currentPage += 2;
        }
    }

    //Starting at the back of the book:
    //set index to end of vector. Check if the page being looked for is either at i or i-1.
    //If not, flip back 2 pages at a time, incrementing a reversePageFlipped counter.
    pageFound = false;
    currentPage = (book.size() - 1);

    while ((!pageFound) && (!beginningOfBook) ) {
        prevPage = book[currentPage - 1];
        if (prevPage == 404) {
           beginningOfBook = true;
        }
        if (currentPage == desiredPage || prevPage == desiredPage) {
            pageFound = true;
        }
        else {
            reversePagesFlipped++;
            currentPage -= 2;
        }
    }
    //Compare pagesTurned starting at the front of the book vs. pages turned starting at the back of the book.
    if (reversePagesFlipped < forwardPagesFlipped) {
        minPagesTurned = reversePagesFlipped;
    }
    else {
        minPagesTurned = forwardPagesFlipped;
    }

    //Whichever method has the least number of pages turned, return that value.
    return minPagesTurned;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string p_temp;
    getline(cin, p_temp);

    int p = stoi(ltrim(rtrim(p_temp)));

    int result = pageCount(n, p);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
            s.begin(),
            find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
            find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
            s.end()
    );

    return s;
}
