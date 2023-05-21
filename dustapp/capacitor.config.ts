import { CapacitorConfig } from '@capacitor/cli';

const config: CapacitorConfig = {
  appId: 'org.lattek.dust',
  appName: 'LattekDust',
  webDir: 'build',
  server: {
    androidScheme: 'https'
  }
};

export default config;
