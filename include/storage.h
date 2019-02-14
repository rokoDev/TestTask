//
//  storage.h
//  fastmap
//
//  Created by roko on 09/02/2019.
//

#ifndef storage_h
#define storage_h

#include <vector>
#include <set>
#include <string>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

namespace pbds = __gnu_pbds;

class storage
{
public:
    storage();
    void insert(const std::string &str);
    const std::string &get(std::size_t index) const;
    
private:
    using ordered_set = pbds::tree<std::string, pbds::null_type, std::less<std::string>, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;
    
    ordered_set _myset;
};

#endif /* storage_h */
