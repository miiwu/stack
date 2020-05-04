#include "main_cfg.h"

#if MAIN_UNIFY_STRUCTURE_EN

#define MAIN_UNIFY_STRUCTURE_STRUCT_EN									0
#define MAIN_UNIFY_STRUCTURE_ADAPTOR_EN									1

void main_unify_struct(void);
void main_unify_adaptor(void);

void main_unify_structure(void)
{
	#if MAIN_UNIFY_STRUCTURE_STRUCT_EN

	main_unify_struct();

	#endif // MAIN_UNIFY_STRUCTURE_STRUCT_EN

	#if MAIN_UNIFY_STRUCTURE_ADAPTOR_EN

	main_unify_adaptor();

	#endif // MAIN_UNIFY_STRUCTURE_ADAPTOR_EN

	return;
}

#if MAIN_UNIFY_STRUCTURE_STRUCT_EN

struct unify_structure_s {
	struct allocator_unit_s allocator_unit;
};

void main_unify_struct(void)
{
	printf("\r\n ------------------------+ unify struct demo start +------------------------\r\n");

	struct unify_structure_s
		*unify_structure = NULL;

	printf("\r\nunify_structure.construct start\r\n");
	unify_structure->allocator_unit
		= unify_struct_control_construct(&unify_structure,
										 CONCEPT_ALLOCATOR,
										 sizeof(struct unify_structure_s));

	printf("\r\nunify_structure.destruct start\r\n");
	if (unify_struct_control_destruct(&unify_structure, unify_structure->allocator_unit)) {
		return;
	}

	printf("\r\n ------------------------+ unify struct demo end +------------------------ \r\n");

	return;
}

#endif // MAIN_UNIFY_STRUCTURE_STRUCT_EN

#if MAIN_UNIFY_STRUCTURE_ADAPTOR_EN

struct unify_adaptor_adaptee_s {
	struct allocator_unit_s allocator_unit;
};

struct unify_adaptor_adaptor_s {
	enum unify_adaptor_adapt_status_e adapt_status;

	struct allocator_unit_s allocator_unit;

	struct unify_adaptor_adaptee_s *adaptee_ptr;
};

void main_unify_adaptor_adaptee_init(struct unify_adaptor_adaptee_s **adaptee, size_t size);
void main_unify_adaptor_adaptee_destroy(struct unify_adaptor_adaptee_s **adaptee);

void main_unify_adaptor(void)
{
	struct unify_adaptor_adaptor_s *unify_adaptor_adaptor = NULL;
	struct unify_adaptor_adaptee_s *unify_adaptor_adaptee = NULL;

	struct unify_adaptor_package_s construct_package = {
		.adaptor.allocator_type = CONCEPT_ALLOCATOR,
		.adaptor.adaptor_memory_size = sizeof(struct unify_adaptor_adaptor_s),
		.adaptor.adaptee_offset
			= DEBUG_MICRO_CONTROL_FIELD_OFFSET(struct unify_adaptor_adaptor_s, adaptee_ptr),
		.adaptor.allocator_unit_offest
			= DEBUG_MICRO_CONTROL_FIELD_OFFSET(struct unify_adaptor_adaptor_s, allocator_unit),

		.adaptee.init_ptr = main_unify_adaptor_adaptee_init,
		.adaptee.init_arg_ptr = { (void *)sizeof(struct unify_adaptor_adaptee_s) },
		.adaptee.destroy_ptr = main_unify_adaptor_adaptee_destroy,
		.adaptee.allocator_unit_offest = DEBUG_MICRO_CONTROL_FIELD_OFFSET(struct unify_adaptor_adaptee_s, allocator_unit),
	};

	printf("\r\n------------------------+ unify adaptor demo start +------------------------\r\n");

	printf("\r\nunify_adaptor.construct start \r\n");
	unify_adaptor_control_construct(&unify_adaptor_adaptor,
									construct_package);
	printf("unify_adaptor.construct end \r\n");

	printf("\r\nunify_adaptor.adapt_exist start \r\n");
	main_unify_adaptor_adaptee_init(&unify_adaptor_adaptee,
									sizeof(struct unify_adaptor_adaptee_s));
	unify_adaptor_control_adapt_exist(&unify_adaptor_adaptor,
									  unify_adaptor_adaptee,
									  construct_package);
	printf("unify_adaptor.adapt_exist end \r\n");

	printf("\r\nunify_adaptor.destruct start \r\n");
	unify_adaptor_control_destruct(&unify_adaptor_adaptor,
								   construct_package);
	main_unify_adaptor_adaptee_destroy(&unify_adaptor_adaptee);
	printf("unify_adaptor.destruct end \r\n");

	printf("\r\n------------------------+ unify adaptor demo end +------------------------\r\n");
}

void main_unify_adaptor_adaptee_init(struct unify_adaptor_adaptee_s **adaptee,
									 size_t size)
{
	(*adaptee)->allocator_unit = unify_struct_control_construct(adaptee, 0, size);

	printf("unify_adaptor.adaptee_init():.adaptee:%p \r\n", *adaptee);
}

void main_unify_adaptor_adaptee_destroy(struct unify_adaptor_adaptee_s **adaptee)
{
	printf("unify_adaptor.adaptee_destroy():.adaptee:%p \r\n", *adaptee);

	unify_struct_control_destruct(adaptee, (*adaptee)->allocator_unit, true);
}

#endif // MAIN_UNIFY_STRUCTURE_ADAPTOR_EN

#endif // MAIN_UNIFY_STRUCTURE_EN