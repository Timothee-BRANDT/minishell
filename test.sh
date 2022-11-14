#!/bin/bash

prompt="${PS1@P}"
function exec_test()
{
	TEST1=$(echo $@ | ./minishell 2>&-)
	echo "${prompt}"
	ES_1=$?
	TEST2=$(echo $@ "; exit" | bash 2>&-)
	ES_2=$?
}


exec_test 'alou'rala'm'iff'looool '                              ' ""'
exec_test 'aloura"lafamille"lol'test''
exec_test 'aloura|"lamiff"'
exec_test '"aloura"la"miff"'
exec_test 'lol"lablague" ca a des bugs'
exec_test ''cat""lol' "lol'laquotes'" mdrrr'lol' "letest'deouf"'"
exec_test '"par contrela'c'est un peu problematique"'
exec_test 'lol""'
exec_test '""'
exec_test 'md""rrrr'
exec_test '""'