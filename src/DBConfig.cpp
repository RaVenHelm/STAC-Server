#include "DBConfig.hpp"

#include <array>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <map>
#include <iostream>

stac::config::DBConfig stac::config::load_db_config_from_file(std::string const& filename)
{
  std::ifstream file{ filename };
  std::vector<std::string> lines;
  std::string line{};
  while(std::getline(file, line))
  {
    lines.push_back(line);
  }
  if(lines.size() == 0) {
    throw std::runtime_error("Config file is missing of is empty");
  }

  if(lines.size() != 5) {
    throw std::runtime_error("File must contain 5 lines");
  }

  std::regex config_regex{ "^(ip|port|username|password|schema)=(.+)$" };
  std::smatch matches{};
  std::map<std::string, std::string> kvp{};

  std::for_each(std::begin(lines), std::end(lines),
    [&](auto const& l){
      auto is_match = std::regex_match(l, matches, config_regex);
      if(is_match)
      {
        // The first match is always the whole matched expression
        for(unsigned i = 1; i < matches.size(); i += 2)
        {
          auto key = matches[i].str();
          auto value = matches[i+1].str();
          kvp.emplace(key, value);
        }
      }
      else
      {
        std::stringstream ss;
        ss << "Invalid config value for line: " << line << '\n';
        throw std::runtime_error(ss.str());
      }
    });

    DBConfig config{};
    std::for_each(std::begin(kvp), std::end(kvp),
      [&](auto const& pair){
        auto k = pair.first;
        if(k == "ip")
        {
          config.ip = pair.second;
        }
        else if(k == "port")
        {
          config.port = pair.second;
        }
        else if(k == "username")
        {
          config.username = pair.second;
        }
        else if(k == "password")
        {
          config.password = pair.second;
        }
        else if(k == "schema")
        {
          config.schema = pair.second;
        }
        else
        {
          std::stringstream ss;
          ss << "Invalid config key: " << k << '\n';
          throw std::runtime_error(ss.str());
        }
      });

      return config;
}

std::string stac::config::connection_string(DBConfig const& config)
{
  std::stringstream ss{};
  ss << config.ip << ':' << config.port;
  return ss.str();
}
