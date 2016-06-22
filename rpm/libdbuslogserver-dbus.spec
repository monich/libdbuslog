Name: libdbuslogserver-dbus
Version: 1.0.2
Release: 0
Summary: Library of logging utilities
Group: Development/Libraries
License: BSD
URL: https://git.merproject.org/mer-core/libdbuslog
Source: %{name}-%{version}.tar.bz2
Requires:   libglibutil >= 1.0.9
BuildRequires:  pkgconfig(libglibutil) >= 1.0.9
BuildRequires: pkgconfig(glib-2.0)
BuildRequires: pkgconfig(dbus-1)
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description
Provides server side for inter-process logging functionaliy

%package devel
Summary: Development library for %{name}
Requires: %{name} = %{version}
Requires: pkgconfig

%description devel
This package contains the development library for %{name}.

%prep
%setup -q

%build
make -C server KEEP_SYMBOLS=1 dbus-release dbus-pkgconfig

%install
rm -rf %{buildroot}
make -C server dbus-install-dev DESTDIR=%{buildroot}

%check
make -C test test

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%{_libdir}/%{name}.so.*

%files devel
%defattr(-,root,root,-)
%{_libdir}/pkgconfig/*.pc
%{_libdir}/%{name}.so
%{_includedir}/dbuslogserver-dbus/*.h
