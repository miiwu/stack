#include "main_cfg.h"

#if MAIN_UNIFY_STRUCTURE_EN

struct unify_structure_s {
	struct allocator_unit_s allocator_unit;
};

void main_unify_structure(void)
{
	printf("\r\n ------------------------+ unify structure demo start +------------------------\r\n");

	struct unify_structure_s
		*unify_structure = NULL;

	printf("\r\nunify_structure.construct start\r\n");
	struct unify_structure_construct_package_s
		construct_package = unify_structure_control_construct(&unify_structure,
															  CONCEPT_ALLOCATOR,
															  sizeof(struct unify_structure_s));
	unify_structure->allocator_unit = construct_package.allocator_unit;
	if (construct_package.error) {
		return;
	}

	printf("\r\nunify_structure.destruct start\r\n");
	if (unify_structure_control_destruct(&unify_structure, unify_structure->allocator_unit)) {
		return;
	}

	printf("\r\n ------------------------+ unify structure demo end +------------------------ \r\n");

	return;
}

#endif // MAIN_UNIFY_STRUCTURE_EN