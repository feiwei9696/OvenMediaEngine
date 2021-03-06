
#include "ovt_private.h"
#include "ovt_application.h"
#include "ovt_stream.h"
#include "ovt_session.h"

std::shared_ptr<OvtApplication> OvtApplication::Create(const info::Application &application_info)
{
	auto application = std::make_shared<OvtApplication>(application_info);
	application->Start();
	return application;
}

OvtApplication::OvtApplication(const info::Application &application_info)
		: Application(application_info)
{

}

OvtApplication::~OvtApplication()
{
	Stop();
	logtd("OvtApplication(%d) has been terminated finally", GetId());
}

bool OvtApplication::Start()
{
	return Application::Start();
}

bool OvtApplication::Stop()
{
	return Application::Stop();
}

std::shared_ptr<pub::Stream> OvtApplication::CreateStream(const std::shared_ptr<info::Stream> &info, uint32_t worker_count)
{
	logtd("OvtApplication::CreateStream : %s/%u", info->GetName().CStr(), info->GetId());
	if(worker_count == 0)
	{
		// RtcStream should have worker threads.
		worker_count = MIN_STREAM_THREAD_COUNT;
	}

	return OvtStream::Create(GetSharedPtrAs<pub::Application>(), *info, worker_count);
}

bool OvtApplication::DeleteStream(const std::shared_ptr<info::Stream> &info)
{
	logtd("OvtApplication::DeleteStream : %s/%u", info->GetName().CStr(), info->GetId());

	auto stream = std::static_pointer_cast<OvtStream>(GetStream(info->GetId()));
	if(stream == nullptr)
	{
		logte("OvtApplication::Delete stream failed. Cannot find stream (%s)", info->GetName().CStr());
		return false;
	}

	auto sessions = stream->GetAllSessions();
	for(auto const &x : sessions)
	{
		auto session = std::static_pointer_cast<OvtSession>(x.second);
	}

	logtd("OvtApplication %s/%s stream has been deleted", GetName().CStr(), stream->GetName().CStr());

	return true;
}