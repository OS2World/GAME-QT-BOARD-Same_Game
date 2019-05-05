Name:		samegame
Version:	1.1.0
Release:	1%{dist}
Summary:	Qt implementation of SameGame.
Group:		Amusements/Games
License:	GPLv3
URL:		http://samegame.sourceforge.net/
Source0:	%{name}-%{version}.tar.gz
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:	qt-devel >= 4.7
Requires:	qt >= 4.7

%description
Qt implementation of SameGame.

%prep
%setup -q

%build
qmake-qt4 . PREFIX=%{_prefix} VERSION=%{version}
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make install INSTALL_ROOT=$RPM_BUILD_ROOT
desktop-file-validate %{buildroot}/%{_datadir}/applications/samegame.desktop

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%doc gpl.txt readme.txt
%{_bindir}/*
%{_datadir}/applications/samegame.desktop
%{_datadir}/icons/hicolor/scalable/apps/samegame.svg

%post
touch --no-create %{_datadir}/icons/hicolor &>/dev/null || :

%postun
if [ $1 -eq 0 ] ; then
    touch --no-create %{_datadir}/icons/hicolor &>/dev/null
    gtk-update-icon-cache %{_datadir}/icons/hicolor &>/dev/null || :
fi

%posttrans
gtk-update-icon-cache %{_datadir}/icons/hicolor &>/dev/null || :

%changelog
* Sat Mar 05 2011 Jari Karppinen <jari.p.karppinen at, gmail.com> 1.1.0-1
- Qt port.

* Sat Mar 05 2011 Jari Karppinen <arkiwursti at, gmail.com> 1.0.1-1
- Started using CMake, desktop entry and icon added, fixes for packaging.

* Wed Aug 12 2009 Jari Karppinen <arkiwursti at, gmail.com> 1.0.0-1
- Initial attempt at packaging.

