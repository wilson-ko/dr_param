/// Catch
#include <catch2/catch.hpp>

/// Fizyr
#include "yaml.hpp"
#include "yaml_decompose.hpp"
#include "decompose_macros.hpp"

namespace dr {
	struct Struct {        //NOLINT
		int a;         //NOLINT
		bool b;        //NOLINT
		std::string c; //NOLINT
	};

	class Class {
		int member_;

	public:
		int       & member()       { return member_; }
		[[nodiscard]] int const & member() const { return member_; }
	};
} //namespace dr

DR_PARAM_DEFINE_STRUCT_DECOMPOSITION(dr::Struct,
	(a, "int", "", true)
	(b, "int", "", true)
	(c, "int", "", true)
);

DR_PARAM_DEFINE_DECOMPOSITION(dr::Class,
	("member", "int", "", true, [] (auto & v) { return &v.member();} )
);

namespace dr {

TEST_CASE("YamlParser 0", "decompose_struct") {
	YAML::Node node = YAML::Load("{a: 7, b: true, c: \"aap noot mies\"}");
	YamlResult<Struct> foo = parseYaml<Struct>(node);
	REQUIRE(foo);
	REQUIRE(foo->a == 7);
	REQUIRE(foo->b == true);
	REQUIRE(foo->c == "aap noot mies");
}

TEST_CASE("YamlParser 1", "decompose_class") {
	YAML::Node node = YAML::Load("{member: 7}");
	YamlResult<Class> foo = parseYaml<Class>(node);
	REQUIRE(foo);
	REQUIRE(foo->member() == 7);
}

} //namespace dr
