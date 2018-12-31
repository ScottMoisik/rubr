#pragma once

#ifdef RUBR_PLATFORM_WINDOWS

extern Rubr::App* Rubr::CreateApp();


int main(int argc, char** argv) {
	Rubr::Log::Init();
	RUBR_CORE_WARN("Initialized Log!");
	int a = 1;
	RUBR_INFO("Hello! Var={0}", a);

	auto app = Rubr::CreateApp();

	app->Run();
	delete app;

}
#endif

#define BIT(x) (1 << x)