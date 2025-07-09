#!/bin/bash



# Solution 1 - Safe

find ~ -type f -newer ~/practice/01/f3 -exec rm -i {} \;


# Solution 2 - Unsafe

find ~ -type f -newer ~/practice/01/f3 -delete
