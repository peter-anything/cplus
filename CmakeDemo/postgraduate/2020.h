//
// Created by peter on 2020/1/19.
//

#ifndef CMAKEDEMO_2020_H
#define CMAKEDEMO_2020_H

void test()
{
    int a[] = {0, 2, 3, 4, 6};
    int b[] = {6, 7, 8, 9, 10};
    int c[] = {1, 2, 5, 6, 9};

    int min = INT32_MAX;
    int index_a = 0;
    int index_b = 0;
    int index_c = 0;

    int min_index_a = 0;
    int min_index_b = 0;
    int min_index_c = 0;

    while (index_a < 5 && index_b < 5 && index_c < 5) {
        int temp_a = a[index_a];
        int temp_b = b[index_b];
        int temp_c = c[index_c];
        int abs_sum = abs(temp_a - temp_b) + abs(temp_a - temp_c) + abs(temp_b - temp_c);
        if (abs_sum < min)
        {
            min = abs_sum;
            min_index_a = index_a;
            min_index_b = index_b;
            min_index_c = index_c;

            if(abs_sum == 0)
            {
                break;
            }
        }

        if(temp_a <= temp_b && temp_a <= temp_c)
        {
            ++index_a;
        }

        if(temp_b <= temp_a && temp_b <= temp_c)
        {
            ++index_b;
        }

        if(temp_c <= temp_a && temp_a <= temp_b)
        {
            ++index_c;
        }
    }

    std::cout << min << '\t' << min_index_a << '\t' << min_index_b << '\t' << min_index_c << std::endl;
}
#endif //CMAKEDEMO_2020_H
