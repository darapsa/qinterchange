#include <cstddef>
#include <memory>
#include <icclient/admin.h>
#include "qicclient/admin.hxx"

namespace QICClient {

	std::shared_ptr<Admin> Admin::logIn(QString const& username,
			QString const& password, QString const& successPage,
			QString const& nextPage, QString const& failPage,
			size_t (*handler)(void*, size_t, size_t, void*))
	{
		auto admin = new Admin{};
		admin->setData(icclient_admin_login(username.toLatin1().constData(),
					password.toLatin1().constData(),
					successPage.toLatin1().constData(),
					nextPage.toLatin1().constData(),
					failPage.toLatin1().constData(),
					handler));
		return std::shared_ptr<Admin>{admin};
	}

	void Admin::setUserName(QString const& userName)
	{
		if (m_userName != userName) {
			m_userName = userName;
			emit userNameChanged();
		}
	}
	void Admin::setPassword(QString const& password)
	{
		if (m_password != password) {
			m_password = password;
			emit passwordChanged();
		}
	}
	void Admin::setName(QString const& name)
	{
		if (m_name != name) {
			m_name = name;
			emit nameChanged();
		}
	}
	void Admin::setSuper(bool super)
	{
		if (m_super != super) {
			m_super = super;
			emit superChanged();
		}
	}

	void Admin::setData(icclient_admin* data)
	{
		if (data && data->username && m_userName != data->username) {
			m_userName = QString{data->username};
			emit userNameChanged();
		} else setUserName("");

		if (data && data->password && m_password != data->password) {
			m_password = QString{data->password};
			emit passwordChanged();
		} else setPassword("");

		if (data && data->name && m_name != data->name) {
			m_name = QString{data->name};
			emit nameChanged();
		} else setName("");

		if (data) setSuper(data->super);
		else setSuper("");

		if (m_data != data) m_data = data;
	}

	void Admin::newItem(QString const& description, QString const& comment,
			QString const& price, QString const& imagePath)
	{
		icclient_admin_newitem(description.toLatin1().constData(),
				comment.toLatin1().constData(),
				price.toLatin1().constData(),
				imagePath.toLatin1().constData());
	}

	void Admin::logOut()
	{
		icclient_admin_logout(m_data);
		setData(nullptr);
	}

}
