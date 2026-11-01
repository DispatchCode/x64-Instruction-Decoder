// SPDX-License-Identifier: GPL-2.0-only

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/utils/function_length.h"

struct expected_result {
	int length;
	const size_t *offsets;
	size_t offset_count;
};

static int check_case(const char *name, const uint8_t *bytes,
					  const struct expected_result *expected)
{
	pFunctionInfo info;
	int failed = 0;

	x64id_set_arch(X64);
	info = getFunctionLength((char *)bytes);
	if (!info) {
		fprintf(stderr, "%s: getFunctionLength returned NULL\n", name);
		return 1;
	}

	if (info->length != expected->length) {
		fprintf(stderr, "%s: expected length=%d, got %d\n", name,
				expected->length, info->length);
		failed = 1;
	}
	if ((size_t)info->pVisited->tos != expected->offset_count) {
		fprintf(stderr, "%s: expected %zu decoded instructions, got %d\n", name,
				expected->offset_count, info->pVisited->tos);
		failed = 1;
	} else {
		uintptr_t base = (uintptr_t)bytes;

		for (size_t i = 0; i < expected->offset_count; i++) {
			size_t actual = (size_t)(info->pVisited->vect[i] - base);
			if (actual != expected->offsets[i]) {
				fprintf(stderr,
						"%s: expected instruction at offset %zu, got %zu\n",
						name, expected->offsets[i], actual);
				failed = 1;
			}
		}
	}

	vector_free(info->pVisited);
	free(info);
	if (!failed)
		printf("PASS %s\n", name);
	return failed;
}

int main(void)
{
	static const uint8_t straight_line[] = {0x90, 0xC3};
	static const size_t straight_line_offsets[] = {0, 1};
	static const struct expected_result straight_line_expected = {
		.length = 1,
		.offsets = straight_line_offsets,
		.offset_count = 2,
	};

	static const uint8_t conditional_branch[] = {0x75, 0x02, 0xC3, 0x90, 0xC3};
	static const size_t conditional_branch_offsets[] = {0, 2, 4};
	static const struct expected_result conditional_branch_expected = {
		.length = 4,
		.offsets = conditional_branch_offsets,
		.offset_count = 3,
	};

	static const uint8_t direct_jump[] = {0xEB, 0x01, 0x90, 0xC3};
	static const size_t direct_jump_offsets[] = {0, 3};
	static const struct expected_result direct_jump_expected = {
		.length = 3,
		.offsets = direct_jump_offsets,
		.offset_count = 2,
	};

	static const uint8_t direct_call[] = {0xE8, 0, 0, 0, 0, 0xC3};
	static const size_t direct_call_offsets[] = {0, 5};
	static const struct expected_result direct_call_expected = {
		.length = 5,
		.offsets = direct_call_offsets,
		.offset_count = 2,
	};

	static const uint8_t indirect_call[] = {0xFF, 0x10, 0xC3};
	static const size_t indirect_call_offsets[] = {0, 2};
	static const struct expected_result indirect_call_expected = {
		.length = 2,
		.offsets = indirect_call_offsets,
		.offset_count = 2,
	};

	static const uint8_t int3[] = {0xCC, 0x90};
	static const size_t int3_offsets[] = {0};
	static const struct expected_result int3_expected = {
		.length = 0,
		.offsets = int3_offsets,
		.offset_count = 1,
	};

	int failed = 0;

	failed |=
		check_case("straight-line", straight_line, &straight_line_expected);
	failed |= check_case("conditional-branch", conditional_branch,
						 &conditional_branch_expected);
	failed |= check_case("direct-jump", direct_jump, &direct_jump_expected);
	failed |= check_case("direct-call-falls-through", direct_call,
						 &direct_call_expected);
	failed |= check_case("indirect-call-falls-through", indirect_call,
						 &indirect_call_expected);
	failed |= check_case("int3-terminates", int3, &int3_expected);

	return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
