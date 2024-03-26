#include <iostream>
#include <vector>
#include <curl/curl.h>
#include "histogram.h"
#include "text.h"
#include "svg.h"


using namespace std;

 struct Input {
        vector<double> numbers;
        size_t bin_count{};
        size_t number_count;

};

Input
input_data(istream& in){  //& �� ������ ����������� ����� �����   istream ��������� ����������� ��������

    setlocale(LC_ALL, "RUSSIAN");

    Input in2;

    bool prompt = true;
    if (prompt) cerr << "������� ���������� �����: ";
    in >> in2.number_count;



    in2.numbers.resize(in2.number_count);

    if (prompt) cerr << "������� ����� ������ �������� �������: ";

    vector<double> numbers(in2.number_count);
    for (size_t i = 0; i < in2.number_count; i++) {
        in >> in2.numbers[i];
    }

    if (prompt) cerr << "������� ���������� ������: ";
    in >> in2.bin_count;

    return in2;
};


int
main(int argc, char* argv[]){

    CURL* curl = curl_easy_init();

    if (argc > 1){

        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);

        exit(1);
    }


    curl_global_init(CURL_GLOBAL_ALL);
    auto in = input_data(cin);
    auto bins = make_histogram(in.numbers, in.bin_count);
    show_histogram_text(bins, in.number_count, in.bin_count);

    return 0;
}


// cin - ���������� ������� ������������ �����
