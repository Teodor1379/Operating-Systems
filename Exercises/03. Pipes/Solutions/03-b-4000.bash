#!/bin/bash



# 03-b-4000



mkdir -p ~/dir5

touch ~/dir5/file{1,2,3}



echo -e "1\n2\n\3\n"                    > ~/dir5/file1;
echo -e "s\n\a\nd\nf\n"                 > ~/dir5/file2;
echo -e "3\n2\n1\n45\n42\n14\n1\n52\n"  > ~/dir5/file3;



printf "Lines: %s\n" "$(wc -l ~/dir5/file1)" && printf "Words: %s\n" "$(wc -w ~/dir5/file1)" && printf "Chars: %s\n" "$(wc -m ~/dir5/file1)";
printf "Lines: %s\n" "$(wc -l ~/dir5/file2)" && printf "Words: %s\n" "$(wc -w ~/dri5/file2)" && printf "Chars: %s\n" "$(wc -m ~/dir5/file2)";
printf "Lines: %s\n" "$(wc -l ~/dir5/file3)" && printf "Words: %s\n" "$(wc -w ~/dir5/file3)" && printf "Chars: %s\n" "$(wc -m ~/dir5/file3)";




printf "Lines: %s\n" "$(wc -l ~/dir5/file1)" && printf "Chars: %s\n" "$(wc -m ~/dir5/file1)";
printf "Lines: %s\n" "$(wc -l ~/dir5/file2)" && printf "Chars: %s\n" "$(wc -m ~/dir5/file2)";
printf "Lines: %s\n" "$(wc -l ~/dir5/file3)" && printf "Chars: %s\n" "$(wc -m ~/dir5/file3)";



cat ~/dir/file{1,2,3} | wc -l;
