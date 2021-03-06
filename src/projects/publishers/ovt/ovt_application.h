#pragma once

#include <base/common_types.h>
#include <base/publisher/application.h>
#include <base/info/session.h>

#include "ovt_stream.h"

class OvtApplication : public pub::Application
{
protected:
	const char* GetApplicationTypeName() const override
	{
		return "OVT Publisher";
	}

public:
	static std::shared_ptr<OvtApplication> Create(const info::Application &application_info);
	OvtApplication(const info::Application &application_info);
	~OvtApplication() final;

private:
	bool Start() override;
	bool Stop() override;

	// Application Implementation
	std::shared_ptr<pub::Stream> CreateStream(const std::shared_ptr<info::Stream> &info, uint32_t worker_count) override;
	bool DeleteStream(const std::shared_ptr<info::Stream> &info) override;
};
