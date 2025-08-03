➜  new_minishell git:(main) ✗ valgrind --track-fds=yes ./minishell
==410155== Memcheck, a memory error detector
==410155== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==410155== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==410155== Command: ./minishell
==410155== 
minishell> << E

PARSED COMMANDS
cmd 1:
[NAME]: (null)
[ARGS]: NULL
[INFILE]: NULL
[OUTFILE]: NULL
[HEREDOC]:  << E
[OUTPUT_TYPE]: STDOUT
[INPUT_TYPE]: HEREDOC

heredoc> E
==410175== 
==410175== FILE DESCRIPTORS: 5 open (3 std) at exit.
==410175== Open file descriptor 103: /usr/share/code/v8_context_snapshot.bin
==410175==    <inherited from parent>
==410175== 
==410175== Open file descriptor 41: /home/armosnie/.config/Code/logs/20250803T142826/ptyhost.log
==410175==    <inherited from parent>
==410175== 
==410175== 
==410175== HEAP SUMMARY:
==410175==     in use at exit: 208,366 bytes in 231 blocks
==410175==   total heap usage: 444 allocs, 213 frees, 228,977 bytes allocated
==410175== 
==410175== LEAK SUMMARY:
==410175==    definitely lost: 27 bytes in 2 blocks
==410175==    indirectly lost: 0 bytes in 0 blocks
==410175==      possibly lost: 0 bytes in 0 blocks
==410175==    still reachable: 208,339 bytes in 229 blocks
==410175==         suppressed: 0 bytes in 0 blocks
==410175== Rerun with --leak-check=full to see details of leaked memory
==410175== 
==410175== For lists of detected and suppressed errors, rerun with: -s
==410175== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
=== BEFORE redirections ===
FD 0: OPEN
FD 1: OPEN
FD 2: OPEN
FD 3: OPEN
FD 4: CLOSED
FD 5: CLOSED
FD 6: CLOSED
FD 7: CLOSED
FD 8: CLOSED
FD 9: CLOSED
==========
=== BEFORE execve ===
FD 0: OPEN
FD 1: OPEN
FD 2: OPEN
FD 3: CLOSED
FD 4: CLOSED
FD 5: CLOSED
FD 6: CLOSED
FD 7: CLOSED
FD 8: CLOSED
FD 9: CLOSED
==========
DEBUG: Restoring fd 3->0 and fd 4->1
dup error 1
: Bad file descriptor
==410180== 
==410180== FILE DESCRIPTORS: 5 open (3 std) at exit.
==410180== Open file descriptor 103: /usr/share/code/v8_context_snapshot.bin
==410180==    <inherited from parent>
==410180== 
==410180== Open file descriptor 41: /home/armosnie/.config/Code/logs/20250803T142826/ptyhost.log
==410180==    <inherited from parent>
==410180== 
==410180== 
==410180== HEAP SUMMARY:
==410180==     in use at exit: 208,370 bytes in 231 blocks
==410180==   total heap usage: 439 allocs, 208 frees, 228,897 bytes allocated
==410180== 
==410180== LEAK SUMMARY:
==410180==    definitely lost: 27 bytes in 2 blocks
==410180==    indirectly lost: 0 bytes in 0 blocks
==410180==      possibly lost: 0 bytes in 0 blocks
==410180==    still reachable: 208,343 bytes in 229 blocks
==410180==         suppressed: 0 bytes in 0 blocks
==410180== Rerun with --leak-check=full to see details of leaked memory
==410180== 
==410180== For lists of detected and suppressed errors, rerun with: -s
==410180== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
DEBUG: Restoring fd 3->0 and fd 4->1
dup error 2
: Bad file descriptor
==410155== 
==410155== FILE DESCRIPTORS: 6 open (3 std) at exit.
==410155== Open file descriptor 3:
==410155==    at 0x49DD07D: pipe (pipe.c:29)
==410155==    by 0x40425D: manage_heredocs (manage_files.c:100)
==410155==    by 0x403A11: pipe_function (exec.c:98)
==410155==    by 0x4012E0: main (main.c:31)
==410155== 
==410155== Open file descriptor 103: /usr/share/code/v8_context_snapshot.bin
==410155==    <inherited from parent>
==410155== 
==410155== Open file descriptor 41: /home/armosnie/.config/Code/logs/20250803T142826/ptyhost.log
==410155==    <inherited from parent>
==410155== 
==410155== 
==410155== HEAP SUMMARY:
==410155==     in use at exit: 208,370 bytes in 231 blocks
==410155==   total heap usage: 441 allocs, 210 frees, 230,393 bytes allocated
==410155== 
==410155== LEAK SUMMARY:
==410155==    definitely lost: 27 bytes in 2 blocks
==410155==    indirectly lost: 0 bytes in 0 blocks
==410155==      possibly lost: 0 bytes in 0 blocks
==410155==    still reachable: 208,343 bytes in 229 blocks
==410155==         suppressed: 0 bytes in 0 blocks
==410155== Rerun with --leak-check=full to see details of leaked memory
==410155== 
==410155== For lists of detected and suppressed errors, rerun with: -s
==410155== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)