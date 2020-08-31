Pod::Spec.new do |s|
  s.name             = 'PathKitCExt'
  s.version          = '1.0.0'
  s.summary          = 'C extensions for PathKit, do not use directly'

  s.description      = <<-DESC
                       DESC

  s.homepage         = 'https://github.com/michaeleisel/PathKitCExt'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'michaeleisel' => 'michael.eisel@gmail.com' }
  s.source           = { :git => 'https://github.com/michaeleisel/PathKitCExt.git', :tag => s.version.to_s }

  s.ios.deployment_target = '8.0'
  s.osx.deployment_target = '10.9'
  s.tvos.deployment_target = '9.0'

  s.source_files = 'Sources/**/*.{h,hh,mm,m,c,cpp,swift}'
end
