#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void PutZeros(std::vector<std::vector<std::string>>& pool) {
    for (auto& ip: pool) {
        for (auto& octet: ip) {
            while (octet.size() < 3) {
                octet.insert(0, "0");
            }
        }
    }
}

void RemoveZeros(std::vector<std::vector<std::string>>& pool) {
    for (auto& ip: pool) {
        for (auto& octet: ip) {
            while (octet[0] == '0') {
                octet.erase(0, 1);
            }
        }
    }
}

void Sort(std::vector<std::vector<std::string>>& pool) {
    PutZeros(pool);
    // Concat and sort.
    std::vector<std::string> concat_ips;
    for (auto& ip: pool) {
        std::string concat_ip{};
        for (auto& octet: ip) {
            concat_ip.append(octet);
        }
        concat_ips.push_back(concat_ip);
    }
    std::sort(concat_ips.begin(), concat_ips.end(), std::greater<std::string>());
    // Split sorted ip strings by octets.
    pool.clear();
    for (auto& concat_ip: concat_ips) {
        std::vector<std::string> splitted_ip{};
        splitted_ip.push_back(concat_ip.substr(0, 3));
        splitted_ip.push_back(concat_ip.substr(3, 3));
        splitted_ip.push_back(concat_ip.substr(6, 3));
        splitted_ip.push_back(concat_ip.substr(9, 3));
        pool.push_back(splitted_ip);
    }
    RemoveZeros(pool);
}

auto Filter(std::vector<std::vector<std::string>>& pool, int first_octet){
    std::vector<std::vector<std::string>> filtered;
    for (auto& ip: pool) {
        if (atoi(ip[0].data()) == first_octet) {
            filtered.push_back(ip);
        }
    }
    return filtered;
}

auto Filter(std::vector<std::vector<std::string>>& pool, int first_octet, int second_octet){
    std::vector<std::vector<std::string>> filtered;
    for (auto& ip: pool) {
        if (atoi(ip[0].data()) == first_octet && atoi(ip[1].data()) == second_octet) {
            filtered.push_back(ip);
        }
    }
    return filtered;
}

auto FilterAny(std::vector<std::vector<std::string>>& pool, int any_octet){
    std::vector<std::vector<std::string>> filtered;
    for (auto& ip: pool) {
        for (auto& octet: ip) {
            if (atoi(octet.data()) == any_octet) {
                filtered.push_back(ip);
            }
        }
    }
    return filtered;
}

void PrintPool(std::vector<std::vector<std::string>>& ip_pool) {
    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";

                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }
}

int main()
{
    try
    {
        std::ifstream f;
        f.open("ip_filter.tsv");
        std::vector<std::vector<std::string>> ip_pool;

        if (f.is_open() ) {
            std::string line;
            while(std::getline(f, line))
            {
                std::vector<std::string> v = split(line, '\t');
                ip_pool.push_back(split(v.at(0), '.'));
            }
        }

        // TODO reverse lexicographically sort
        Sort(ip_pool);
        PrintPool(ip_pool);
        auto filtered = Filter(ip_pool, 1);
        PrintPool(filtered);
        filtered = Filter(ip_pool, 46, 70);
        PrintPool(filtered);
        filtered = FilterAny(ip_pool, 46);
        PrintPool(filtered);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
