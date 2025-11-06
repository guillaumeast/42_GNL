#!/usr/bin/env zsh

target="test_gnl"
buffer_size_values=(0 1 2 10 42 1000 9999 10000000)

tests_dir="tests"
inputs_dir="${tests_dir}/inputs"
expected_dir="${tests_dir}/expected"
output_dir="${tests_dir}/outputs"

passed=0
failed=0
total=0

main()
{
	init
	# Test each buffer_size
	for buffer_size in $buffer_size_values; do
		compile $buffer_size

		# Test each input_file
		for f in "${inputs_dir}"/*; do
			filename="$(basename "$f")"
			input_file="${inputs_dir}/${filename}"
			expected_file="${expected_dir}/${filename}"
			output_file="${output_dir}/${filename}"

			# Test with file as argument
			./"${target}" "${input_file}" | cat -e > "${output_file}"
			check_output "./${target} ${input_file}" "${expected_file}" "${output_file}"

			# Test with file as stdin
			output_file="${output_dir}/stdin_${filename}"
			cat "${input_file}" | ./"${target}" | cat -e > "${output_file}"
			check_output "cat ${input_file} | ./${target}" "${expected_file}" "${output_file}"
		done
	done
	print_results
}

init()
{
	rm -f "${target}"
	rm -r "${output_dir}" || true
	mkdir -p "${output_dir}"
}

compile()
{
	local buffer_size=$1

	cc -Wall -Wextra -Werror -D BUFFER_SIZE=$buffer_size \
		main.c ../get_next_line.c ../get_next_line_utils.c -I.. \
			-o "${target}"
}

check_output()
{
	local test_name="$1"
	local expected_file="$2"
	local output_file="$3"

	if [[ ! -f "$expected_file" ]]; then
		echo "⚠️ Missing expected file: $expected_file"
		((failed++))
	elif diff -q "${expected_file}" "${output_file}" > /dev/null; then
		((passed++))
	else
		((failed++))
		echo "------------------------------"
		echo
		echo "❌ ${test_name}"
		echo
		echo "⮕ diff ${expected_file} ${output_file}"
		echo
		diff "${expected_file}" "${output_file}"
		echo
		echo "------------------------------"
	fi
	((total++))
}

print_results()
{
	echo
	if (( failed == 0 )); then
		echo "===> ✅ ${passed} / ${total} tests passed"
		exit 0
	else
		echo "===> ❌ ${failed} / ${total} tests failed"
		exit 1
	fi
}

main
