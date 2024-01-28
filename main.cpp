#include <algorithm>
#include <array>
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

using IpType = std::array<uint8_t, 4>;

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

void PutZerosToIp(std::vector<std::string>& ip) {
    for (auto& octet: ip) {
        while (octet.size() < 3) {
            octet.insert(0, "0");
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

auto IpStrsToDigit(std::vector<std::string>& ip_strs) {
    PutZerosToIp(ip_strs);
    // Concat
    std::string str_ip_with_zeros;
    for (auto& str_octet: ip_strs) {
        str_ip_with_zeros.append(str_octet);
    }
    return atol(str_ip_with_zeros.data());
}

void SortStr(std::vector<std::vector<std::string>>& pool) {
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

auto FilterStr(std::vector<std::vector<std::string>>& pool, int first_octet, int second_octet){
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

void PrintPoolFromStr(std::vector<std::vector<std::string>>& ip_pool) {
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

auto GetOctetsFromIpDigit(const uint64_t ip_digit) {
    IpType octets;
    auto ip = ip_digit;
    for (int i = 3; i >= 0; i--) {
        octets[i] = static_cast<uint8_t>(ip % 1000);
        ip /= 1000;
    }
    return octets;
}

auto FilterU64(std::vector<uint64_t>& pool, int first_octet){
    std::vector<uint64_t> filtered;    
    for (auto& ip: pool) {
        auto octets = GetOctetsFromIpDigit(ip);
        if (octets[0] == first_octet) {
            filtered.push_back(ip);
        }
    }
    return filtered;
}

auto FilterArrayOctets(std::vector<IpType>& pool, int first_octet){
    std::vector<IpType> filtered;    
    for (auto& ip: pool) {
        if (ip[0] == first_octet) {
            filtered.push_back(ip);
        }
    }
    return filtered;
}

auto FilterArrayOctets(std::vector<IpType>& pool, int first_octet, int second_octet){
    std::vector<IpType> filtered;    
    for (auto& ip: pool) {
        if (ip[0] == first_octet && ip[1] == second_octet) {
            filtered.push_back(ip);
        }
    }
    return filtered;
}

auto FilterArrayOctetsAny(std::vector<IpType>& pool, int any_octet){
    std::vector<IpType> filtered;    
    for (auto& ip: pool) {
        for (auto& octet: ip) {            
            if (octet == any_octet) {
                filtered.push_back(ip);
                break;
            }
        }
    }
    return filtered;
}

auto FilterU64(std::vector<uint64_t>& pool, int first_octet, int second_octet){
    std::vector<uint64_t> filtered;    
    for (auto& ip: pool) {
        auto octets = GetOctetsFromIpDigit(ip);
        if (octets[0] == first_octet && octets[1] == second_octet) {
            filtered.push_back(ip);
        }
    }
    return filtered;
}

auto FilterAny64(std::vector<uint64_t>& pool, int any_octet){
    std::vector<uint64_t> filtered;
    for (auto& ip: pool) {
        auto octets = GetOctetsFromIpDigit(ip);
        for (auto& octet: octets) {            
            if (octet == any_octet) {
                filtered.push_back(ip);
            }
        }
    }
    return filtered;
}

void PrintPoolU64(std::vector<uint64_t>& ip_pool) {
    for (const auto& digit_ip: ip_pool) {       
        auto octets = GetOctetsFromIpDigit(digit_ip);
        // Print octets.
        for (auto it = octets.cbegin(); it != octets.cend(); ++it) {
            if (it != octets.cbegin()) {
                std::cout << ".";
            }
            std::cout << +*it;
        }
        std::cout << std::endl;
    }
}

void PrintPoolArrayOctets(std::vector<IpType>& ip_pool) {     
    for (const auto& octets: ip_pool) {       
        // Print octets.
        for (auto it = octets.cbegin(); it != octets.cend(); ++it) {
            if (it != octets.cbegin()) {
                std::cout << ".";
            }
            std::cout << +*it;
        }
        std::cout << std::endl;
    }
}

void SortArrayOctets(std::vector<IpType>& ip_pool) {     
    std::sort(ip_pool.begin(), ip_pool.end(), std::greater<>{});        
}

int main()
{
    try
    {
        std::ifstream f;
        f.open("ip_filter.tsv");
        std::vector<IpType> ip_pool{};

        if (f.is_open() ) {
            std::string line;
            while(std::getline(f, line))
            {
                std::vector<std::string> v = split(line, '\t');
                v = split(v.at(0), '.');
                auto ip_digit = IpStrsToDigit(v);
                ip_pool.push_back(GetOctetsFromIpDigit(ip_digit));
            }
        }

        SortArrayOctets(ip_pool);
        PrintPoolArrayOctets(ip_pool);
        auto filtered = FilterArrayOctets(ip_pool, 1);
        PrintPoolArrayOctets(filtered);
        filtered = FilterArrayOctets(ip_pool, 46, 70);
        PrintPoolArrayOctets(filtered);
        filtered = FilterArrayOctetsAny(ip_pool, 46);
        PrintPoolArrayOctets(filtered);

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
