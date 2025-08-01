#!/bin/bash



# 03-b-3500



find /bin -type f -exec cat {} ';' | grep "#!/bin/" | wc -l

find /bin -type f -exec cat {} ';' | grep 'ASCII text executable' | wc -l
